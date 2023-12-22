/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2023/12/22 13:54:01 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	handle_infile(t_pipe *pipe_struct)
{
	int		fd;
	char	*input_file;

	if (pipe_struct->input_file != NULL)
	{
		input_file = pipe_struct->input_file;
		fd = open(input_file, O_RDONLY);
		if (fd == -1)
		{
			perror("Minishell: handle_infile");
			return (0);
		}
		dup2(fd, 0);
		close(fd);
	}
	return (1);
}

int	handle_outfile(t_pipe *pipe_struct)
{
	int		fd;
	char	*output_file;

	assert (pipe_struct->output_file == NULL || pipe_struct->output_file_append == NULL);
	if (pipe_struct->output_file != NULL)
	{
		output_file = pipe_struct->output_file;
		fd = open(output_file, O_RDONLY);
	}
	if (pipe_struct->output_file_append != NULL)
	{
		output_file = pipe_struct->output_file;
		fd = open(output_file, O_RDONLY | O_APPEND);
	}
	if (fd == -1)
	{
		perror("Minishell: handle_outfile");
		return (0);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}

bool	set_exit_value(int exit_value)
{
	char	*environment_var;
	char	*argv[3];

	argv[1] = "?";
	argv[2] = NULL;
	if (! unset(argv))
		return (false);
	environment_var = ft_strjoin("?=", ft_itoa(exit_value));
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
		if (close(fd_array[i][0]) == -1)
		{
			perror("Minishell: close_all_fds");
			return (0);
		}
		if (close(fd_array[i][1]) == -1)
		{
			perror("Minishell: close_all_fds");
			return (0);
		}
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

int	launch_inbuilt(t_process *process, int (*fd_array)[2], size_t p_amount, size_t i)
{
	bool	(*inbuilt) (char** argv);
	int		temp;

	inbuilt = process->inbuilt;
	close_last_fds(fd_array, i);
	if (p_amount > 1 && i != p_amount - 1)
	{
		temp = dup(1);
		dup2(fd_array[i][1], 1);
	}
	if (inbuilt(process->argv) == false)
		return (0);
	if (p_amount > 1 && i != p_amount - 1)
	{
		dup2(temp, 1);
		close(temp);
	}
	return (1);
}

int	find_full_path(t_process *process)
{
	char		**split;
	char		**split2;
	char		*path;
	char		*name1;
	char		*name2;
	int			found = 0;

	if (process->name[0] == '/')
		return (1);

	path = getenv("PATH");
	if (path == NULL)
		return (error_wrapper());
	split = ft_split(path, ':');
	if (split == NULL)
		return (error_wrapper());
	split2 = split;

	while (*split != NULL)
	{
		name1 = ft_strjoin(*split, "/");
		if (name1 == NULL)
			return (-1);
		name2 = ft_strjoin(name1, process->name);
		if (name2 == NULL)
		{
			free(name1);
			return (-1);
		}
		free(name1);
		if (access(name2, F_OK) == 0)
		{
			//free(process->name);
			process->name = name2;
			found = 1;
			break;
		}
		free(name2);
		split++;
	}
	if (found == 0)
	{
		name1 = malloc(1000);
		if (name1 == NULL)
			return (-1);
		name1 = getcwd(name1, 1000);
		name1[ft_strlen(name1)] = '/';
		name1[ft_strlen(name1) + 1] = '\0';
		name2 = ft_strjoin(name1, process->name);
		if (name2 == NULL)
		{
			free(name1);
			return (-1);
		}
		free(name1);
		if (access(name2, F_OK) == 0)
		{
			//free(process->name);
			process->name = name2;
		}
	}

	while (*split2 == NULL)
	{
		free(*split2);
		split2++;
	}
	free(split2);
	return (1);
}

int	launch_process(t_process *process, int (*fd_array)[2], size_t p_amount, size_t i)
{
	char 		*program;
	char 		**argv;
	int			pid;
	extern char	**environ;

	program = process->name;
	argv = process->argv;
	pid = fork();

	if (pid == 0)
	{
		if (i != 0)
			dup2(fd_array[i - 1][0], 0);
		if (i != p_amount - 1)
			dup2(fd_array[i][1], 1);
		close_all_fds(fd_array, p_amount);
		if (find_full_path(process) == -1)
			return (0);
		if (execve(process->name, argv, environ) == -1)
			perror("Minishell: launch_process");
		return (0);
	}
	else
	{
		close_last_fds(fd_array, i);
		return (pid);
	}
}

bool	is_inbuilt(t_process *process)
{
	const char	*function_names[6] = {"cd", "echo", "env", "export", "pwd", "unset"};
	const t_function_pointer	function_pointers[6] = {cd, echo, env, export, pwd, unset};
	char		*name;
	int			i;

	name = process->name;
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(name, function_names[i], 7) == 0)
		{
			process->inbuilt = function_pointers[i];
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

	if (handle_infile(pipe_struct) == 0)
		return (0);
	if (handle_outfile(pipe_struct) == 0)
		return (0);
	i = 0;
	while (i < pipe_struct->p_amount)
	{
		process = pipe_struct->processes[i];
		if (is_inbuilt(&process) == 0)
		{
			pid = launch_process(&process, fd_array, pipe_struct->p_amount, i);
			if (pid == 0)
				return (0);
			pid_array[i] = pid;
		}
		else
		{
			return_value = launch_inbuilt(&process, fd_array, pipe_struct->p_amount, i);
			if (return_value == 0)
				return (0);
			pipe_struct->last_exit_value = return_value;
		}
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
	if (last_pid == -1)
		return (0);
	pipe_struct->last_exit_value = status_pointer;
	if (! set_exit_value(pipe_struct->last_exit_value))
		return (0);

	printf("pid of last process %d\n", last_pid); //debug
	//env(NULL); debug

	return (1);
}

//==========

// int main()
// {
// 	t_pipe pipe_struct;
// 	char *argv1[4];
// 	char *argv2[4];
// 	char *argv3[4];

// 	pipe_struct.p_amount = 2;

// 	argv1[0] = "pwd";
// 	argv1[1] = "a";
// 	argv1[2] = "b";
// 	argv1[3] = NULL;

// 	argv2[0] = "cat";
// 	argv2[1] = NULL;
// 	argv2[2] = NULL;
// 	argv2[3] = NULL;

// 	argv3[0] = "env";
// 	argv3[1] = NULL;
// 	argv3[2] = "bestie";
// 	argv3[3] = NULL;

// 	pipe_struct.input_file = NULL;
// 	pipe_struct.output_file = NULL;
// 	pipe_struct.output_file_append = NULL;

// 	pipe_struct.processes[0].name = "pwd";
// 	// pipe_struct.processes[0].name = "echo";
// 	pipe_struct.processes[0].argv = argv1;

// 	// pipe_struct.processes[1].name = "/Users/marschul/minishell_github/src/execute_line/dummy2";
// 	pipe_struct.processes[1].name = "cat";
// 	pipe_struct.processes[1].argv = argv2;

// 	pipe_struct.processes[2].name = "env";
// 	pipe_struct.processes[2].argv = argv3;
// 	execute_line(&pipe_struct);
// }
