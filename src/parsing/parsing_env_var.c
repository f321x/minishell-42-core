/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:01:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/04 16:51:49 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	fetch_env_var(t_parsing *p, char *buffer, char ***current_argv)
{
	char	*env_var;

	env_var = getenv(buffer);
	if (env_var == NULL)
		return (true);
	*current_argv = append_string(*current_argv, env_var);
	if (!(*current_argv))
		return (false);
	return (true);
}

void	fill_buffer(char *buffer, size_t buffer_s,
					char *string, size_t *str_index)
{
	size_t	buffer_i;

	buffer_i = 0;
	ft_memset(buffer, '\0', buffer_s);
	while (buffer_i < buffer_s &&
			string && ft_isalnum(string[*str_index]))
	 	buffer[buffer_i++] = string[(*str_index)++];
}

bool	parse_env_var(t_parsing *p)
{
	char		buffer[PROC_FIELD_BUFFER];
	char		***current_argv;

	p->inp_i++;
	current_argv = &(p->task->processes[p->task->p_amount].argv);
	fill_buffer(buffer, PROC_FIELD_BUFFER, p->u_input, &(p->inp_i));
	if (ft_strlen(buffer) == 0)
	{
		*current_argv = append_string(*current_argv, "$");
		if (!(*current_argv))
			return (false);
		p->inp_i++;
		return (true);
	}
	return (fetch_env_var(p, buffer, current_argv));
}
