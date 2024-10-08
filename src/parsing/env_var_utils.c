/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:46:10 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/12 15:19:03 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	fill_buffer(char *buffer, size_t buffer_s, t_parsing *p)
{
	size_t	buffer_i;

	buffer_i = 0;
	ft_memset(buffer, '\0', buffer_s);
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ')
	{
		if (p->u_input[p->inp_i] == 39)
		{
			if (!parse_single_quote(p, buffer, &buffer_i))
				return (false);
		}
		else if (p->u_input[p->inp_i] == '"')
		{
			if (!parse_double_quote(p, buffer, &buffer_i))
				return (false);
		}
		else if (p->u_input[p->inp_i] == '$')
			fill_env_in_buffer(p, buffer, &buffer_i);
		else
			buffer[buffer_i++] = p->u_input[p->inp_i++];
	}
	return (true);
}

bool	parse_env_var(t_parsing *p)
{
	char		buffer[PROC_FIELD_BUFFER];
	char		***current_argv;

	p->inp_i++;
	current_argv = &(p->task->processes[p->task->p_amount].argv);
	if (!fill_buffer(buffer, PROC_FIELD_BUFFER, p))
		return (false);
	if (ft_strlen(buffer) == 0)
	{
		*current_argv = append_string(*current_argv, "$");
		if (!(*current_argv))
			return (false);
		if (p->u_input[p->inp_i])
			p->inp_i++;
		return (true);
	}
	return (fetch_env_var(buffer, current_argv));
}

void	fill_env_in_buffer(t_parsing *p, char *buffer, size_t *buffer_i)
{
	char		env_buffer[PROC_FIELD_BUFFER];
	char		*env_var;

	p->inp_i++;
	ft_memset(env_buffer, '\0', PROC_FIELD_BUFFER);
	if (!ft_isalnum(p->u_input[p->inp_i]))
	{
		buffer[(*buffer_i)++] = '$';
		return ;
	}
	fill_env_buffer(env_buffer, p);
	env_var = getenv(env_buffer);
	if (env_var != NULL)
	{
		ft_strlcat(buffer, env_var, PROC_FIELD_BUFFER);
		*buffer_i += ft_strlen(env_var);
	}
}
