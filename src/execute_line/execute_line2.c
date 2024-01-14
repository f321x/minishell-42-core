/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:30:25 by marschul          #+#    #+#             */
/*   Updated: 2024/01/14 21:30:50 by marschul         ###   ########.fr       */
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
