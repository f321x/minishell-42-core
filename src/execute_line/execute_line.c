/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2024/01/14 21:20:32 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(t_process *process)
{
	const char					*function_names[6] = {"cd", "echo", "env", \
	"export", "pwd", "unset"};
	const t_function_pointer	function_pointers[7] = {cd, echo, env, export, \
		pwd, unset};
	char						*name;
	int							i;

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

bool	launch_builtin_in_parent(t_process *process)
{
	if (process->builtin(process->argv) == true)
		return (true);
	else
		return (false);
}

pid_t	launch_process_in_parent(t_process *process)
{
	pid_t		pid;
	extern char	**environ;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (!find_full_path(process))
			error_wrapper_exit("Minishell: launch_process_in_parent");
		if (execve(process->argv[0], process->argv, environ) == -1)
			error_wrapper_exit("Minishell: launch_process_in_parent");	
	}
	return (pid);
}

int	launch_process_in_pipe(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array, \
	size_t i)
{
	int			pid;
	extern char	**environ;
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		close_all_fds(fd_array, p_amount);
		if (process->argv == NULL)
			exit(0);
		if (is_exit(process->argv[0]))
			exit((int) _exit_(process->argv, pipe_struct, fd_array, pid_array));
		if (is_builtin(process))
			exit((int) process->builtin(process->argv));
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

bool	execute_single_command(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
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

int	execute_pipe(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	t_process	process;
	size_t		i;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		process = pipe_struct->processes[i];
		pid_array[i] = launch_process_in_pipe(pipe_struct, fd_array, pid_array, i);
		if (pid_array[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

bool	execute_commands(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
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
