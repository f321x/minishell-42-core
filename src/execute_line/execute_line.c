/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2024/01/09 17:56:22 by marschul         ###   ########.fr       */
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
		unlink("tmp");
	return (0);
}

int	create_pid_array(pid_t **pid_array, size_t p_amount)
{
	*pid_array = malloc(p_amount * sizeof(p_amount));
	if (*pid_array == NULL)
	{
		perror("Minishell: create_pid_array");
		return (0);
	}
	else
		return (1);
}

int	create_fd_array(int (*(*fd_array))[2], size_t n)
{
	int	(*res)[2];

	res = (int (*)[2]) malloc(sizeof(int[n][2]));
	*fd_array = res;
	if (*fd_array == NULL)
	{
		perror("Minishell: create_fd_array");
		return (0);
	}
	else
	{
		(*fd_array)[n - 1][0] = dup(0);
		(*fd_array)[n - 1][1] = dup(1);
		return (1);
	}
}

int	create_pipes(int (*fd_array)[2], size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pipe(fd_array[i]) == -1)
		{
			perror("Minishell: create_pipes");
			return (0);
		}
		i++;
	}
	return (1);
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
	{
		perror("Minishell: handle_infile");
		return (false);
	}
	dup2(fd, 0);
	close(fd);
	return (true);
}

bool	handle_herefile(t_inoutfiles *file, int true_stdin, int true_stdout)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = get_here_file(name, true_stdin, true_stdout);
	if (fd == -1)
	{
		perror("Minishell: handle_herefile");
		return (false);
	}
	dup2(fd, 0);
	close(fd);
	return (true);
}

bool	handle_outfile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Minishell: handle_outfile");
		return (false);
	}
	dup2(fd, 1);
	close(fd);
	return (true);
}

bool	handle_appendfile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd == -1)
	{
		perror("Minishell: handle_appendfile");
		return (false);
	}
	dup2(fd, 1);
	close(fd);
	return (true);
}

bool	handle_inoutfiles(t_process *process, int true_inout_fds[2])
{
	int				i;
	int				return_value;
	t_inoutfiles	*file;
	int		true_stdin;
	int		true_stdout;

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
		return (false);
	argv[1] = environment_var;
	if (! export(argv))
		return (false);
	return (true);
}

int	close_all_fds(int (*fd_array)[2], size_t p_amount)
{
	size_t	i;

	i = 0;
	while (i < p_amount - 1)
	{
		close(fd_array[i][0]);
		close(fd_array[i][1]);
		i++;
	}
	return (1);
}


int	close_last_fds(int (*fd_array)[2], size_t i)
{
	if (i == 0)
		return (1);
	else
	{
		if (close(fd_array[i - 1][0]) == -1)
		{
			perror("Minishell: close_last_fds");
			return (0);
		}
		if (close(fd_array[i - 1][1]) == -1)
		{
			perror("Minishell: close_last_fds");
			return (0);
		}
	}
	return (1);
}

int	launch_builtin(t_process *process, int (*fd_array)[2], size_t p_amount, size_t i)
{
	bool	(*builtin) (char** argv);
	int		temp_out;

	builtin = process->builtin;
	close_last_fds(fd_array, i);
	temp_out = dup(1);
	if (p_amount > 1 && i != p_amount - 1)
	{
		dup2(fd_array[i][1], 1);
	}
	handle_inoutfiles(process, fd_array[p_amount - 1]);
	if (process->argv[0] != NULL)
	{
		if (builtin(process->argv) == false)
			return (0);
	}
	dup2(temp_out, 1);
	close(temp_out);
	return (1);
}

// char	*join_path_and_program_name(char *path, char *name)
// {
// 	char	*full_path;
// 	char	*path_plus_slash;

// 	path_plus_slash = malloc(ft_strlen(path) + 2);
// 	if (path_plus_slash == NULL)
// 		return (NULL);
// 	ft_strlcpy(path_plus_slash, path, ft_strlen(path) + 1);
// 	path_plus_slash[ft_strlen(path) + 1] = '\0';
// 	path_plus_slash[ft_strlen(path)] = '/';
// 	full_path = ft_strjoin(path_plus_slash, name);
// 	free(path_plus_slash);
// 	return (full_path);
// }

// bool	find_full_path_in_path_var(t_process *process, char *paths)
// {
// 	char	*full_path;
// 	char	**split;
// 	int		i;

// 	split = ft_split(paths, ':');
// 	if (split == NULL)
// 		return (error_wrapper());
// 	i = 0;
// 	while (split[i] != NULL)
// 	{
// 		full_path = join_path_and_program_name(split[i], process->argv[0]);
// 		if (access(full_path, F_OK) == 0)
// 		{
// 			free(process->argv[0]);
// 			process->argv[0] = full_path;
// 			break;
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	free_vector(split);
// 	return (true);
// }

// bool	find_full_path(t_process *process)
// {
// 	char	cwd[PATH_MAX];
// 	char	*old_path_var_with_colon;
// 	char	*new_path_var;
// 	char	*paths;
// 	char	*name;

// 	name = process->argv[0];
// 	if (name[0] == '/')
// 		return (true);
// 	paths = getenv("PATH");
// 	getcwd(cwd, PATH_MAX);
// 	old_path_var_with_colon = ft_strjoin(paths, ":");
// 	if (old_path_var_with_colon == NULL)
// 		return (false);
// 	new_path_var = ft_strjoin(old_path_var_with_colon, cwd);
// 	free(old_path_var_with_colon);
// 	if (!find_full_path_in_path_var(process, new_path_var))
// 		return (error_wrapper());
// 	free(new_path_var);
// 	return (true);
// }

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
	int		full_path_index;
	char	*start;
	char	*end;
	int		endflag = false;

	name = process->argv[0];
	if (name[0] == '/')
		return (true);
	paths = getenv("PATH");
	if (paths == NULL || ft_strlen(paths) == 0)
		return (true);
	start = paths;
	end = paths;
	while (*end != '\0' && !endflag)
	{
		if (*start == ':' && *(end + 1) == '\0')
			endflag = true;
		full_path_index = 0;
		end = ft_strchr(start, ':');
		if (end == NULL)
			end = ft_strchr(start, '\0');
		if (start == end || *start != '/') 
		{
			full_path[0] = '.';
			full_path[1] = '/';
			full_path_index += 2;
		}
		ft_memcpy(full_path + full_path_index, start, end - start);
		full_path_index += end - start;
		full_path[full_path_index] = '/';
		full_path_index++;
		ft_memcpy(full_path + full_path_index, name, ft_strlen(name));
		full_path_index += ft_strlen(name);
		full_path[full_path_index] = '\0';
		ft_printf("%s\n", full_path);
		if (check_path(process, full_path))
			return (true);
		start = end;
		if (*start == ':' && *(start + 1) != '\0')
			start++;
	}
	return (false);
}

int	launch_process(t_process *process, int (*fd_array)[2], size_t p_amount, size_t i)
{
	char 		**argv;
	int			pid;
	extern char	**environ;

	argv = process->argv;
	if (i != 0)
	{
		dup2(fd_array[i - 1][0], 0);
	}
	if (i != p_amount - 1)
	{
		dup2(fd_array[i][1], 1);
	}
	if (! handle_inoutfiles(process, fd_array[p_amount - 1]))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close_all_fds(fd_array, p_amount);
		if (!find_full_path(process))
		{
			perror("Minishell: launch_process");
			exit(1);
		}
		printf("%s\n", process->argv[0]);
		if (execve(process->argv[0], argv, environ) == -1)
			perror("Minishell: launch_process");
		exit(1);
	}
	else
	{
		close_last_fds(fd_array, i);
		dup2(fd_array[p_amount - 1][0], 0);
		dup2(fd_array[p_amount - 1][1], 1);
		return (pid);
	}
}

bool	is_exit(char *name)
{
	if (name == NULL)
		return (false);
	else
		return (ft_strncmp("exit", name, 5) == 0);
}

bool	is_builtin(t_process *process)
{
	const char	*function_names[6] = {"cd", "echo", "env", "export", "pwd", "unset"};
	const t_function_pointer	function_pointers[7] = {cd, echo, env, export, pwd, unset};
	char		*name;
	int			i;

	name = process->argv[0];
	if (name == NULL)
		return (true);
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

int	execute_commands(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	int			pid;
	int			return_value;
	t_process	process;
	size_t		i;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		process = pipe_struct->processes[i];
		assert(process.argv != NULL);
		if (is_exit(process.argv[0]))
		{
			_exit_(process.argv, pipe_struct, fd_array, pid_array);
		}
		if (is_builtin(&process) == 0)
		{
			pid = launch_process(&process, fd_array, pipe_struct->p_amount, i);
			if (pid == 0)
				return (0);
			pid_array[i] = pid;
		}
		else
		{
			return_value = launch_builtin(&process, fd_array, pipe_struct->p_amount, i);
			pid_array[i] = return_value;
		}
		i++;
	}
	return (1);
}


bool	wait_for_all(pid_t *pid_array, t_pipe *pipe_struct)
{
	int	last_pid;
	size_t	i;
	int	status_pointer;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		if (pid_array[i] == 0 || pid_array[i] == 1)
		{
			set_exit_value(1 - pid_array[i]);
			i++;
			continue;
		}
		last_pid = waitpid(pid_array[i], &status_pointer, 0);
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
		if (last_pid == -1)
			return (false);
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
	if (create_pid_array(&pid_array, p_amount) == 0)
		return (cleanup(pipe_struct, fd_array, pid_array));
	if (create_fd_array(&fd_array, p_amount) == 0)
		return (cleanup(pipe_struct, fd_array, pid_array));
	if (create_pipes(fd_array, p_amount - 1) == 0)
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

// 	pipe_struct.p_amount = 3;

// 	argv1[0] = ft_strdup("cat");
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

// 	one.name = ft_strdup("here");
// 	one.type = HEREDOC;
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
