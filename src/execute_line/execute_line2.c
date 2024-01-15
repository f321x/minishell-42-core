/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:30:25 by marschul          #+#    #+#             */
/*   Updated: 2024/01/15 15:16:21 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
This is the child process in the pipe:
We set signal handlers back to default.
We close all file descriptors that we don't need, since otherwise the process
does not terminate.
We differ between exit builtin, builtin or process.
 */
void	execute_child_process(t_pipe *pipe_struct, int (*fd_array)[2], \
pid_t *pid_array, size_t i)
{
	t_process	*process;
	extern char	**environ;

	process = &pipe_struct->processes[i];
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close_all_fds(fd_array, pipe_struct->p_amount);
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

/* 
This does not only decide if it is a builtin, but sets also the function
pointer to the rigth function.
 */
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
