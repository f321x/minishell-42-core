/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2024/01/10 00:32:45 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cleanup(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	size_t	i;
	long	j;

	free(pid_array);
	free(fd_array);
	i = 0;
	while (i < pipe_struct->p_amount)
	{
		free_vector(pipe_struct->processes[i].argv);
		j = 0;
		while (j < pipe_struct->processes[i].io_amount)
		{
			free(pipe_struct->processes[i].iofiles[j].name);
			j++;
		}
		i++;
	}
	if (access("tmp", F_OK) == 0)
		if (unlink("tmp") == -1)
			perror("Minishell: cleanup");
	return (0);
}

bool	create_pid_array(pid_t **pid_array, size_t p_amount)
{
	*pid_array = malloc(p_amount * sizeof(p_amount));
	if (*pid_array == NULL)
		return (error_wrapper_bool("Minishell: create_pid_array"));
	else
		return (true);
}

bool	create_fd_array(int (*(*fd_array))[2], size_t n)
{
	int	(*res)[2];

	res = (int (*)[2])malloc(sizeof(int [n][2]));
	*fd_array = res;
	if (*fd_array == NULL)
		return (error_wrapper_bool("Minishell: create_fd_array"));
	(*fd_array)[n - 1][0] = dup(0);
	(*fd_array)[n - 1][1] = dup(1);
	return (true);
}

bool	create_pipes(int (*fd_array)[2], size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pipe(fd_array[i]) == -1)
			return (error_wrapper_bool("Minishell: create_pipes"));
		i++;
	}
	return (true);
}

int	get_here_file(char *keyword, int true_stdin, int true_stdout)
{
	int		fd;
	bool	end;
	ssize_t	bytes_read;
	ssize_t	bytes_written;
	ssize_t	i;
	char	full_path[1];

	fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	i = 0;
	end = false;
	while (!end)
	{
		if (i == 0)
			bytes_written = write(true_stdout, ">", 1);
		bytes_read = read(true_stdin, full_path, 1);
		if (i != -1)
		{
			if (full_path[0] == keyword[i])
				i++;
			else
			{
				if (full_path[0] == '\n')
					if (i == (ssize_t) ft_strlen(keyword))
						end = true;
					else
					{
						bytes_written = write(fd, keyword, i);
						i = 0;
						bytes_written = write(fd, full_path, 1);
					}
				else
				{
					bytes_written = write(fd, keyword, i);
					i = -1;
					bytes_written = write(fd, full_path, 1);
				}
			}
		}
		else
		{
			bytes_written = write(fd, full_path, 1);
			if (full_path[0] == '\n')
				i = 0;
		}
	}
	close(fd);
	fd = open("tmp", O_RDONLY, 0600);
	return (fd);
}

bool	handle_infile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_RDONLY | O_NONBLOCK, 0600);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_infile"));
	if (dup2(fd, 0) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_infile"));
	return (true);
}

bool	handle_herefile(t_inoutfiles *file, int true_stdin, int true_stdout)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = get_here_file(name, true_stdin, true_stdout);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_herefile"));
	if (dup2(fd, 0) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_herefile"));
	return (true);
}

bool	handle_outfile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_outfile"));
	if (dup2(fd, 1) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_outfile"));
	return (true);
}

bool	handle_appendfile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_appendfile"));
	if (dup2(fd, 1) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_appendfile"));
	return (true);
}

bool	handle_inoutfiles(t_process *process, int true_inout_fds[2])
{
	int				i;
	int				return_value;
	t_inoutfiles	*file;
	int				true_stdin;
	int				true_stdout;

	true_stdin = true_inout_fds[0];
	true_stdout = true_inout_fds[1];
	i = 0;
	while (i < process->io_amount)
	{
		file = &process->iofiles[i];
		if (file->type == IN)
			return_value = handle_infile(file);
		if (file->type == OUT)
			return_value = handle_outfile(file);
		if (file->type == HEREDOC)
			return_value = handle_herefile(file, true_stdin, true_stdout);
		if (file->type == APPEND)
			return_value = handle_appendfile(file);
		if (return_value == false)
			return (false);
		i++;
	}
	return (true);
}

bool	set_exit_value(int exit_value)
{
	char	*environment_var;
	char	*argv[3];
	char	*number_as_string;

	argv[0] = "export";
	argv[2] = NULL;
	number_as_string = ft_itoa(WEXITSTATUS(exit_value));
	environment_var = ft_strjoin("?=", number_as_string);
	free(number_as_string);
	if (environment_var == NULL)
		return (error_wrapper_bool("Minishell: set_exit_value"));
	argv[1] = environment_var;
	if (! export(argv))
		return (false);
	return (true);
}

void	close_all_fds(int (*fd_array)[2], size_t p_amount)
{
	size_t	i;

	i = 0;
	while (i < p_amount - 1)
	{
		close(fd_array[i][0]);
		close(fd_array[i][1]);
		i++;
	}
}

bool	close_last_fds(int (*fd_array)[2], size_t i)
{
	if (i == 0)
		return (1);
	else
	{
		if (close(fd_array[i - 1][0]) == -1)
			return (error_wrapper_bool("Minishell: close_last_fds"));
		if (close(fd_array[i - 1][1]) == -1)
			return (error_wrapper_bool("Minishell: close_last_fds"));
	}
	return (true);
}

int	launch_builtin(t_process *process, int (*fd_array)[2], size_t p_amount, \
	size_t i)
{
	t_function_pointer	builtin;

	builtin = process->builtin;
	if (! close_last_fds(fd_array, i))
		return (0);
	if (p_amount > 1 && i != p_amount - 1)
	{
		if (dup2(fd_array[i][1], 1) == -1)
			return (error_wrapper_int("Minishell: launch_builtin"));
	}
	if (! handle_inoutfiles(process, fd_array[p_amount - 1]))
		return (0);
	if (process->argv != NULL)
	{
		if (builtin(process->argv) == false)
			return (0);
	}
	if (dup2(fd_array[p_amount - 1][1], 1) == -1)
		return (error_wrapper_int("Minishell: launch_builtin"));
	if (dup2(fd_array[p_amount - 1][0], 0) == -1)
		return (error_wrapper_int("Minishell: launch_builtin"));
	return (1);
}

bool	expand_path_var(char *paths, char new_paths[1000])
{
	int		i;

	i = 0;
	while (*paths != '\0')
	{
		if (*paths == ':' && (*(paths + 1) == ':' || *(paths + 1) == '\0'))
		{
			new_paths[i] = ':';
			new_paths[i + 1] = '.';
			i += 1;
		}
		else
			new_paths[i] = *paths;
		i++;
		if (i >= 998)
			return (false);
		paths++;
	}
	new_paths[i] = ':';
	new_paths[i + 1] = '\0';
	return (true);
}

int	concatenate_path_with_name(char *start, char *name, \
	char full_path[PATH_MAX])
{
	int		full_path_index;
	char	*end;

	full_path_index = 0;
	end = ft_strchr(start, ':');
	ft_memcpy(full_path, start, end - start);
	full_path_index += end - start;
	full_path[full_path_index] = '/';
	full_path_index++;
	ft_memcpy(full_path + full_path_index, name, ft_strlen(name));
	full_path_index += ft_strlen(name);
	full_path[full_path_index] = '\0';
	return (full_path_index - ft_strlen(name));
}

bool	check_path(t_process *process, char path[PATH_MAX])
{
	if (access(path, F_OK) == 0)
	{
		free(process->argv[0]);
		process->argv[0] = ft_strdup(path);
		return (true);
	}
	return (false);
}

bool	find_full_path(t_process *process)
{
	char	*paths;
	char	*name;
	char	full_path[PATH_MAX];
	char	new_paths[1000];
	char	*start;

	paths = getenv("PATH");
	if (paths == NULL || ft_strlen(paths) == 0)
		return (true);
	name = process->argv[0];
	if (name[0] == '/' || ft_strlen(name) >= 2 && name[0] == '.' && \
		name[1] == '/' || ft_strlen(name) >= 3 && name[0] == '.' && \
		name[1] == '.' && name[2] == '/')
		return (true);
	if (! expand_path_var(paths, new_paths))
		return (false);
	start = new_paths;
	while (*start != '\0')
	{
		start += concatenate_path_with_name(start, name, full_path);
		if (check_path(process, full_path))
			return (true);
	}
	return (false);
}

bool	is_exit(char *name)
{
	return (ft_strncmp("exit", name, 5) == 0);
}

bool	is_builtin(t_process *process)
{
	const char					*function_names[6] = {"cd", "echo", "env", \
	"export", "pwd", "unset"};
	const t_function_pointer	function_pointers[7] = {cd, echo, env, export, \
		pwd, unset};
	char						*name;
	int							i;

	if (process->argv == NULL)
		return (true);
	name = process->argv[0];
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(name, function_names[i], 7) == 0)
		{
			process->builtin = function_pointers[i];
			return (true);
		}
		i++;
	}
	return (false);
}

int	launch_process(t_process *process, int (*fd_array)[2], size_t p_amount, \
	size_t i)
{
	int			pid;
	extern char	**environ;

	if (i != 0)
		dup2(fd_array[i - 1][0], 0);
	if (i != p_amount - 1)
		dup2(fd_array[i][1], 1);
	if (! handle_inoutfiles(process, fd_array[p_amount - 1]))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close_all_fds(fd_array, p_amount);
		if (!find_full_path(process))
			error_wrapper_exit("Minishell: launch_process");
		if (execve(process->argv[0], process->argv, environ) == -1)
			error_wrapper_exit("Minishell: launch_process");
	}
	close_last_fds(fd_array, i);
	dup2(fd_array[p_amount - 1][0], 0);
	dup2(fd_array[p_amount - 1][1], 1);
	return (pid);
}

int	execute_commands(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	t_process	process;
	size_t		i;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		process = pipe_struct->processes[i];
		if (process.argv && is_exit(process.argv[0]))
			_exit_(process.argv, pipe_struct, fd_array, pid_array);
		if (is_builtin(&process) == 0)
		{
			pid_array[i] = launch_process(&process, fd_array, \
				pipe_struct->p_amount, i);
			if (pid_array[i] == 0)
				return (0);
		}
		else
			pid_array[i] = launch_builtin(&process, fd_array, \
				pipe_struct->p_amount, i);
		i++;
	}
	return (1);
}

bool	check_for_signaled_quit(int status_pointer)
{
	if (WIFSIGNALED(status_pointer) && WTERMSIG(status_pointer) == 3)
	{
		ft_printf("Quit: 3\n");
		set_exit_value(131);
		return (true);
	}
	if (WIFSIGNALED(status_pointer) && WTERMSIG(status_pointer) == 2)
	{
		set_exit_value(130);
		return (true);
	}
	return (false);
}

bool	wait_for_all(pid_t *pid_array, t_pipe *pipe_struct)
{
	size_t	i;
	int		status_pointer;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		if (pid_array[i] == 0 || pid_array[i] == 1)
		{
			set_exit_value(1 - pid_array[i]);
			i++;
			continue ;
		}
		if (waitpid(pid_array[i], &status_pointer, 0) == -1)
			return (false);
		if (check_for_signaled_quit(status_pointer))
			return (true);
		i++;
	}
	if (! set_exit_value(status_pointer))
		return (false);
	return (true);
}

int	execute_line(t_pipe *pipe_struct)
{
	size_t	p_amount;
	pid_t	*pid_array;
	int		(*fd_array)[2];

	p_amount = pipe_struct->p_amount;
	pid_array = NULL;
	fd_array = NULL;
	if (! create_pid_array(&pid_array, p_amount))
		return (cleanup(pipe_struct, fd_array, pid_array));
	if (! create_fd_array(&fd_array, p_amount))
		return (cleanup(pipe_struct, fd_array, pid_array));
	if (! create_pipes(fd_array, p_amount - 1))
		return (cleanup(pipe_struct, fd_array, pid_array));
	if (execute_commands(pipe_struct, fd_array, pid_array) == 0)
		return (cleanup(pipe_struct, fd_array, pid_array));
	if (! wait_for_all(pid_array, pipe_struct))
		return (cleanup(pipe_struct, fd_array, pid_array));
	cleanup(pipe_struct, fd_array, pid_array);
	return (1);
}

//==========

// int main()
// {
// 	t_pipe pipe_struct;
// 	char **argv1 = malloc(4 * sizeof(char *));
// 	char **argv2 = malloc(4 * sizeof(char *));
// 	char **argv3 = malloc(4 * sizeof(char *));
// 	t_inoutfiles	one;
// 	t_inoutfiles	two;
// 	t_inoutfiles	three;

// 	pipe_struct.p_amount = 1;

// 	argv1[0] = ft_strdup("echo");
// 	argv1[1] = NULL;
// 	argv1[2] = NULL;
// 	argv1[3] = NULL;

// 	argv2[0] = ft_strdup("ls");
// 	argv2[1] = NULL;
// 	argv2[2] = NULL;
// 	argv2[3] = NULL;

// 	argv3[0] = ft_strdup("wc");
// 	argv3[1] = ft_strdup("-c");
// 	argv3[2] = NULL;
// 	argv3[3] = NULL;

// 	one.name = ft_strdup("file.txt");
// 	one.type = IN;
// 	two.name = "f2";
// 	two.type = OUT;
// 	three.name = "here2";
// 	three.type = HEREDOC;

// 	pipe_struct.processes[0].argv = argv1;
// 	pipe_struct.processes[1].argv = argv2;
// 	pipe_struct.processes[2].argv = argv3;

// 	pipe_struct.processes[0].iofiles[0] = one;
// 	pipe_struct.processes[0].iofiles[1] = two;
// 	pipe_struct.processes[0].iofiles[2] = three;

// 	pipe_struct.processes[0].io_amount = 1;
// 	pipe_struct.processes[1].io_amount = 0;
// 	pipe_struct.processes[2].io_amount = 0;

// 	execute_line(&pipe_struct);
// }
