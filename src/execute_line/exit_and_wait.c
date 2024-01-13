/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:09:09 by marschul          #+#    #+#             */
/*   Updated: 2024/01/13 18:37:03 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	set_exit_value(int exit_value)
{
	char	*environment_var;
	char	*argv[3];
	char	*number_as_string;

	argv[0] = "export";
	argv[2] = NULL;
	number_as_string = ft_itoa(exit_value);
	environment_var = ft_strjoin("?=", number_as_string);
	free(number_as_string);
	if (environment_var == NULL)
		return (error_wrapper_bool("Minishell: set_exit_value"));
	argv[1] = environment_var;
	if (! export(argv))
		return (false);
	free(environment_var);
	return (true);
}

bool	is_exit(char *name)
{
	return (ft_strncmp("exit", name, 5) == 0);
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

	status_pointer = 0;
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
			return (false);
		i++;
	}
	if (! set_exit_value(WEXITSTATUS(status_pointer)))
		return (false);
	return (true);
}
