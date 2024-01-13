/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:12:33 by marschul          #+#    #+#             */
/*   Updated: 2024/01/13 14:28:29 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (builtin(process->argv) == false)
			return (0);
	if (dup2(fd_array[p_amount - 1][1], 1) == -1)
		return (error_wrapper_int("Minishell: launch_builtin"));
	if (dup2(fd_array[p_amount - 1][0], 0) == -1)
		return (error_wrapper_int("Minishell: launch_builtin"));
	return (1);
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
