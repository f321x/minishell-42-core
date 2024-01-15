/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2024/01/15 15:13:20 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
The file descriptors are set for the pipe. Afterwards they will be restored
for the parent process.
We open the indirections.
We fork.
I put the code for the child process in another function for norminette 
reasons.
 */
int	launch_process_in_pipe(t_pipe *pipe_struct, int (*fd_array)[2], \
pid_t *pid_array, size_t i)
{
	int			pid;
	t_process	*process;
	size_t		p_amount;

	p_amount = pipe_struct->p_amount;
	if (i != 0)
		dup2(fd_array[i - 1][0], 0);
	if (i != p_amount - 1)
		dup2(fd_array[i][1], 1);
	process = &pipe_struct->processes[i];
	if (! handle_inoutfiles(process, fd_array[p_amount - 1]))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		execute_child_process(pipe_struct, fd_array, pid_array, i);
	}
	close_last_fds(fd_array, i);
	dup2(fd_array[p_amount - 1][0], 0);
	dup2(fd_array[p_amount - 1][1], 1);
	return (pid);
}

/* 
A single command must be treated differently, since the builtin will not
run in a childprocess.
Nevertheless we have to open the indirections.
exit is being called from here, since it needs a lot of variables as
parameters.
 */
bool	execute_single_command(t_pipe *pipe_struct, int (*fd_array)[2], \
	pid_t *pid_array)
{
	t_process	process;

	process = pipe_struct->processes[0];
	if (! handle_inoutfiles(&process, fd_array[pipe_struct->p_amount - 1]))
		return (false);
	if (process.argv == NULL)
		return (true);
	if (is_exit(process.argv[0]))
		_exit_(process.argv, pipe_struct, fd_array, pid_array);
	if (is_builtin(&process))
	{
		if (! launch_builtin_in_parent(&process))
			return (false);
		pid_array[0] = 1;
	}
	else
	{
		pid_array[0] = launch_process_in_parent(&process);
		if (pid_array[0] == 0)
			return (false);
	}
	return (true);
}

/* 
We loop over the processes in the pipe.
 */
int	execute_pipe(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	t_process	process;
	size_t		i;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		process = pipe_struct->processes[i];
		pid_array[i] = launch_process_in_pipe(pipe_struct, fd_array, \
			pid_array, i);
		if (pid_array[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

/* 
We must make a difference between single command and pipe.
 */
bool	execute_commands(t_pipe *pipe_struct, int (*fd_array)[2], \
	pid_t *pid_array)
{
	if (pipe_struct->p_amount <= 1)
	{
		if (! execute_single_command(pipe_struct, fd_array, pid_array))
			return (false);
	}
	else
	{
		if (! execute_pipe(pipe_struct, fd_array, pid_array))
			return (false);
	}
	return (true);
}

/*
main fuction:
We alloc the data structure, create the pipes, execute the one command or 
the pipe, then we wait for all processes to come home.
In case of error we free all resources in cleanup.
 */
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
	if (! execute_commands(pipe_struct, fd_array, pid_array))
	{
		set_exit_value(1);
		return (cleanup(pipe_struct, fd_array, pid_array));
	}
	if (! wait_for_all(pid_array, pipe_struct))
		return (cleanup(pipe_struct, fd_array, pid_array));
	cleanup(pipe_struct, fd_array, pid_array);
	return (1);
}
