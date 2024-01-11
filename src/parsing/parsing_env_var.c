/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:01:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/11 14:39:55 by ***REMOVED***            ###   ########.fr       */
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

// static void	parse_dq_assignment(t_parsing *p, char *assignment_buffer,
// 								size_t *ass_buff_i)
// {
// 	char	env_key_buffer[PROC_FIELD_BUFFER];
// 	char	*env_var;

// 	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != '"')
// 	{
// 		if (p->u_input[p->inp_i] == '$')
// 		{
// 			p->inp_i++;
// 			if (p->u_input[p->inp_i] == ' ' || p->u_input[p->inp_i] == '"')
// 			{
// 				assignment_buffer[(*ass_buff_i)++] = '$';
// 				continue ;
// 			}
// 			fill_buffer(env_key_buffer, PROC_FIELD_BUFFER,
// 				p->u_input, &(p->inp_i));
// 			env_var = getenv(env_key_buffer);
// 			if (env_var != NULL)
// 			{
// 				ft_strlcat(assignment_buffer, env_var, PROC_FIELD_BUFFER);
// 				*ass_buff_i += ft_strlen(env_var);
// 			}
// 		}
// 		else
// 			assignment_buffer[(*ass_buff_i)++] = p->u_input[p->inp_i++];
// 	}
// }

// parse assignment without quotes
// static void	parse_assignment(t_parsing *p, char *assignment_buffer,
// 								size_t *ass_buff_i)
// {
// 	char	env_key_buffer[PROC_FIELD_BUFFER];
// 	char	*env_var;

// 	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ')
// 	{
// 		if (p->u_input[p->inp_i] == '$' && p->inp_i++)
// 		{
// 			if (p->u_input[p->inp_i] == ' ')
// 			{
// 				assignment_buffer[(*ass_buff_i)++] = '$';
// 				break ;
// 			}
// 			fill_buffer(env_key_buffer, PROC_FIELD_BUFFER,
// 				p->u_input, &(p->inp_i));
// 			env_var = getenv(env_key_buffer);
// 			if (env_var != NULL)
// 			{
// 				ft_strlcat(assignment_buffer, env_var, PROC_FIELD_BUFFER);
// 				*ass_buff_i += ft_strlen(env_var);
// 			}
// 			break ;
// 		}
// 		else
// 			assignment_buffer[(*ass_buff_i)++] = p->u_input[p->inp_i++];
// 	}
// }

// parsing for key=value, key='value', key="value", key="$value" and key=$value
bool	parse_env_assignment(t_parsing *p, char *buffer, size_t *buffer_i)
{
	buffer[(*buffer_i)++] = p->u_input[p->inp_i++];
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ')
	{
		if (p->u_input[p->inp_i] == 39)
		{
			if (!parse_single_quote(p, buffer, buffer_i))
				return (false);
		}
		else if (p->u_input[p->inp_i] == '"')
		{
			if (!parse_double_quote(p, buffer, buffer_i))
				return (false);
		}
		else if (p->u_input[p->inp_i] == '$')
			fill_env_in_buffer(p, buffer, buffer_i);
		else
			buffer[(*buffer_i)++] = p->u_input[p->inp_i++];
	}
	return (true);
}
