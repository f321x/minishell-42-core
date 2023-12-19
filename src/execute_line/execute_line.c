/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2023/12/19 17:22:03 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pid_array(pid_t **pid_array, size_t p_amount)
{
	*pid_array = malloc(p_amount * sizeof(p_amount));
	if (*pid_array == NULL)
		return (0);
	else
		return (1);
}

int	create_fd_array(int (*(*fd_array))[2], size_t n)
{
	int	(*res)[2];

	res = malloc(sizeof(int[n][2]));
	*fd_array = res;
	if (*fd_array == NULL)
		return (0);
	else
		return (1);
}

int	create_pipes(int (*fd_array)[2], size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pipe(fd_array[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	handle_infile(t_pipe *pipe_struct)
{
	int	fd;
	char	*input_file;

	input_file = pipe_struct->input_file;
	fd = open(input_file, O_RDONLY);
	dup2(fd, 0);
}

void	handle_outfile(t_pipe *pipe_struct)
{
	int	fd;
	char	*output_file;

	output_file = pipe_struct->output_file;
	fd = open(output_file, O_RDONLY);
	dup2(fd, 1);
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


void	close_last_fds(int (*fd_array)[2], size_t i)
{
	if (i == 0)
		return ;
	else
	{
		close(fd_array[i - 1][0]);
		close(fd_array[i - 1][1]);
	}
}

void	launch_inbuilt(t_process *process, int (*fd_array)[2], size_t i)
{
	bool	(*inbuilt) (char** argv);
	int		temp;

	close_last_fds(fd_array, i);
	temp = dup(1);
	dup2(fd_array[i][1], 1);
	inbuilt = process->inbuilt;
	if (inbuilt(process->argv) == false)
		return ;
	dup2(temp, 1);
	return ;
}

int	launch_process(t_process *process, int (*fd_array)[2], size_t p_amount, size_t i)
{
	char *program;
	char **argv;
	int	pid;
	extern char		**environ;

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
		execve(program, argv, environ);
	}
	else
	{
		close_last_fds(fd_array, i);
		return (pid);
	}
	return (1);
}

bool	is_inbuilt(t_process *process)
{
	const char	*function_names[6] = {"cd", "echo", "env", "export", "pwd", "unset"};
	const t_function_pointer	function_pointers[6] = {cd};
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

void	execute_programs(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	size_t			n;
	int				pid;
	t_process		process;
	size_t			i;

	n = pipe_struct->p_amount;

	handle_infile(pipe_struct);
	handle_outfile(pipe_struct);

	i = 0;
	while (i < n)
	{
		process = pipe_struct->processes[i];
		if (is_inbuilt(&process) == 0)
		{
			pid = launch_process(&process, fd_array, pipe_struct->p_amount, i);
			pid_array[i] = pid;
		}
		else
			launch_inbuilt(&process, fd_array, i);
		i++;
	}
}

int	execute_line(t_pipe *pipe_struct)
{
	size_t	p_amount;
	pid_t	*pid_array;
	int		(*fd_array)[2];
	pid_t	last_pid;
	int		status_pointer;

	p_amount = pipe_struct->p_amount;
	create_pid_array(&pid_array, p_amount);
	create_fd_array(&fd_array, p_amount - 1);
	create_pipes(fd_array, p_amount - 1);
	execute_programs(pipe_struct, fd_array, pid_array);
	last_pid = waitpid(pid_array[p_amount - 1], &status_pointer, 0);
	printf("status %d %d", last_pid, WEXITSTATUS(status_pointer));
	return (1);
}

//==========

int main()
{
	t_pipe pipe_struct;
	char *argv[4];

	pipe_struct.p_amount = 1;
	
	argv[0] = "/bin/cat";
	argv[1] = "src/execute_line/testfile";
	argv[2] = "/Users/marschul/minishell_github/src/execute_line/test.c";
	argv[3] = NULL;

	pipe_struct.processes = malloc(pipe_struct.p_amount * sizeof(t_process));
	// pipe_struct.processes[0].name = "/Users/marschul/minishell_github/src/execute_line/dummy1";
	pipe_struct.processes[0].name = "/bin/cat";
	pipe_struct.processes[0].argv = argv;
	// pipe_struct.processes[1].name = "/Users/marschul/minishell_github/src/execute_line/dummy2";
	// pipe_struct.processes[1].name = "/usr/bin/wc";
	// pipe_struct.processes[1].argv = argv;
	// pipe_struct.processes[1].env = env;
	execute_line(&pipe_struct);
}
