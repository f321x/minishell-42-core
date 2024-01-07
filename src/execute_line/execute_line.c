/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2024/01/07 18:44:43 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup(t_process *process)
{
	// free all resources of the process, including a temp file
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

	res = malloc(sizeof(int[n][2]));
	*fd_array = res;
	if (*fd_array == NULL)
	{
		perror("Minishell: create_fd_array");
		return (0);
	}
	else
		return (1);
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
	char	buffer[1];

	fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	i = 0;
	end = false;
	while (!end)
	{
		if (i == 0)
			bytes_written = write(true_stdout, ">", 1);
		bytes_read = read(true_stdin, buffer, 1);
		if (i != -1)
		{
			if (buffer[0] == keyword[i])
				i++;
			else
			{
				if (buffer[0] == '\n')
					if (i == ft_strlen(keyword))
						end = true;
					else
					{
						bytes_written = write(fd, keyword, i);
						i = 0;
						bytes_written = write(fd, buffer, 1);
					}
				else
				{
					bytes_written = write(fd, keyword, i);
					i = -1;
					bytes_written = write(fd, buffer, 1);
				}
			}
		}
		else
		{
			bytes_written = write(fd, buffer, 1);
			if (buffer[0] == '\n')
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

bool	handle_inoutfiles(t_process *process)
{
	int				i;
	int				return_value;
	t_inoutfiles	*file;
	static int		true_stdin;
	static int		true_stdout;

	// Das funktioniert nicht! Wir lesen mehrere Command lines!
	// if (true_stdin == 0 && true_stdout == 0)
	// {
	// 	true_stdin = dup(0);
	// 	true_stdout = dup(1);
	// }
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

	argv[0] = "export";
	argv[2] = NULL;
	environment_var = ft_strjoin("?=", ft_itoa(exit_value)); //ft_itoa malloced, wir muessen freeen!
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
		// if (close(fd_array[i][0]) == -1)
		// {
		// 	ft_printf("%d 0", i);
		// 	perror("Minishell: close_all_fds");
		// 	return (0);
		// }
		// if (close(fd_array[i][1]) == -1)
		// {
		// 	ft_printf("%d 1", i);
		// 	perror("Minishell: close_all_fds");
		// 	return (0);
		// }
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
	handle_inoutfiles(process);
	if (builtin(process->argv) == false)
		return (0);
	dup2(temp_out, 1);
	close(temp_out);
	return (1);
}

char	*join_path_and_program_name(char *path, char *name)
{
	char	*full_path;
	char	*path_plus_slash;

	path_plus_slash = malloc(ft_strlen(path) + 2);
	if (path_plus_slash == NULL)
		return (NULL);
	ft_strlcpy(path_plus_slash, path, ft_strlen(path) + 1);
	path_plus_slash[ft_strlen(path) + 1] = '\0';
	path_plus_slash[ft_strlen(path)] = '/';
	full_path = ft_strjoin(path_plus_slash, name);
	free(path_plus_slash);
	return (full_path);
}

bool	find_full_path_in_path_var(t_process *process, char *paths)
{
	char	*full_path;
	char	**split;
	int		i;

	split = ft_split(paths, ':');
	if (split == NULL)
		return (error_wrapper());
	i = 0;
	while (split[i] != NULL)
	{
		full_path = join_path_and_program_name(split[i], process->argv[0]);
		if (access(full_path, F_OK) == 0)
		{
			//free(process->argv[0]);
			process->argv[0] = full_path;
			break;
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (true);
}

bool	find_full_path(t_process *process)
{
	char	cwd[PATH_MAX];
	char	*old_path_var_with_colon;
	char	*new_path_var;
	char	*paths;
	char	*name;

	name = process->argv[0];
	if (name[0] == '/')
		return (true);
	paths = getenv("PATH");
	getcwd(cwd, PATH_MAX);
	old_path_var_with_colon = ft_strjoin(paths, ":");
	if (old_path_var_with_colon == NULL)
		return (false);
	new_path_var = ft_strjoin(old_path_var_with_colon, cwd);
	free(old_path_var_with_colon);
	if (!find_full_path_in_path_var(process, new_path_var))
		return (error_wrapper());
	return (true);
}

int	launch_process(t_process *process, int (*fd_array)[2], size_t p_amount, size_t i)
{
	char 		**argv;
	int			pid;
	extern char	**environ;

	argv = process->argv;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (i != 0)
		{
			dup2(fd_array[i - 1][0], 0);
		}
		if (i != p_amount - 1)
		{
			dup2(fd_array[i][1], 1);
		}
		close_all_fds(fd_array, p_amount);
		handle_inoutfiles(process);
		if (!find_full_path(process))
			return (0);
		if (execve(process->argv[0], argv, environ) == -1)
			perror("Minishell: launch_process");
		return (0);
	}
	else
	{
		close_last_fds(fd_array, i);
		return (pid);
	}
}

bool	is_builtin(t_process *process)
{
	const char	*function_names[7] = {"cd", "echo", "env", "export", "pwd", "unset", "exit"};
	const t_function_pointer	function_pointers[7] = {cd, echo, env, export, pwd, unset, _exit_};
	char		*name;
	int			i;

	name = process->argv[0];
	i = 0;
	while (i < 7)
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
		if (process.argv == NULL)
			continue;
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
			if (return_value == 0)
				return (0);
			pipe_struct->last_exit_value = return_value;
		}
		cleanup(&process);
		i++;
	}
	return (1);
}

int	execute_line(t_pipe *pipe_struct)
{
	size_t	p_amount;
	pid_t	*pid_array;
	int		(*fd_array)[2];
	pid_t	last_pid;
	int		status_pointer;

	p_amount = pipe_struct->p_amount;
	if (create_pid_array(&pid_array, p_amount) == 0)
		return (0);
	if (create_fd_array(&fd_array, p_amount - 1) == 0)
		return (0);
	if (create_pipes(fd_array, p_amount - 1) == 0)
		return (0);
	if (execute_commands(pipe_struct, fd_array, pid_array) == 0)
		return (0);
	last_pid = waitpid(pid_array[p_amount - 1], &status_pointer, 0);
	if (WIFSIGNALED(status_pointer) && WTERMSIG(status_pointer) == 3)
		ft_printf("Quit: 3\n");
	if (last_pid == -1)
		return (0);
	pipe_struct->last_exit_value = status_pointer;
	if (! set_exit_value(pipe_struct->last_exit_value))
		return (0);

	printf("pid of last process %d\n", last_pid); //debug
	return (1);
}

//==========

// int main()
// {
// 	t_pipe pipe_struct;
// 	char *argv1[4];
// 	char *argv2[4];
// 	char *argv3[4];
// 	t_inoutfiles	one;
// 	t_inoutfiles	two;
// 	t_inoutfiles	three;

// 	pipe_struct.p_amount = 3;

// 	argv1[0] = "ls";
// 	argv1[1] = NULL;
// 	argv1[2] = NULL;
// 	argv1[3] = NULL;

// 	argv2[0] = "ls";
// 	argv2[1] = NULL;
// 	argv2[2] = NULL;
// 	argv2[3] = NULL;

// 	argv3[0] = "ls";
// 	argv3[1] = NULL;
// 	argv3[2] = NULL;
// 	argv3[3] = NULL;

// 	one.name = "f1";
// 	one.type = HEREDOC;
// 	two.name = "f2";
// 	two.type = HEREDOC;
// 	three.name = "f3";
// 	three.type = OUT;

// 	pipe_struct.processes[0].argv = argv1;
// 	pipe_struct.processes[1].argv = argv2;
// 	pipe_struct.processes[2].argv = argv3;

// 	pipe_struct.processes[0].iofiles[0] = one;
// 	pipe_struct.processes[0].iofiles[1] = two;
// 	pipe_struct.processes[0].iofiles[2] = three;

// 	pipe_struct.processes[0].io_amount = 0;
// 	pipe_struct.processes[1].io_amount = 0;
// 	pipe_struct.processes[2].io_amount = 0;

// 	execute_line(&pipe_struct);
// }
