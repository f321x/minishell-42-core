/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:01:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/12 14:25:16 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	append_last_string(char *env_var,
								char ***current_argv, char *argv_buffer)
{
	if (env_var && !(*env_var))
	{
		*current_argv = append_string(*current_argv, argv_buffer);
		if (!(*current_argv))
			return (false);
	}
	return (true);
}

bool	fetch_env_var(char *buffer, char ***current_argv)
{
	char	argv_buffer[PROC_FIELD_BUFFER];
	char	*env_var;
	size_t	argv_buff_i;

	env_var = getenv(buffer);
	if (env_var == NULL)
		return (true);
	ft_memset(argv_buffer, '\0', PROC_FIELD_BUFFER);
	argv_buff_i = 0;
	while (env_var && *env_var)
	{
		if (*env_var == ' ')
		{
			env_var++;
			*current_argv = append_string(*current_argv, argv_buffer);
			if (!(*current_argv))
				return (false);
			ft_memset(argv_buffer, '\0', PROC_FIELD_BUFFER);
			argv_buff_i = 0;
		}
		else
			argv_buffer[argv_buff_i++] = *(env_var++);
	}
	return (append_last_string(env_var, current_argv, argv_buffer));
}
