/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:01:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/09 16:28:27 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	append_last_string(char *env_var, char ***current_argv, char *argv_buffer)
{
	if (env_var && !(*env_var))
	{
		*current_argv = append_string(*current_argv, argv_buffer);
		if (!(*current_argv))
			return (false);
	}
	return (true);
}

static bool	fetch_env_var(t_parsing *p, char *buffer, char ***current_argv)
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
	if (!append_last_string(env_var, current_argv, argv_buffer))
		return (false);
	return (true);
}

void	fill_buffer(char *buffer, size_t buffer_s,
					char *string, size_t *str_index)
{
	size_t	buffer_i;

	buffer_i = 0;
	ft_memset(buffer, '\0', buffer_s);
	if (buffer_i < buffer_s && string && string[*str_index] == '?')
		buffer[buffer_i++] = string[(*str_index)++];
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
		if (p->u_input[p->inp_i])
			p->inp_i++;
		return (true);
	}
	return (fetch_env_var(p, buffer, current_argv));
}

static void	parse_dq_assignment(t_parsing *p, char *assignment_buffer,
								size_t *ass_buff_i)
{
	char	env_key_buffer[PROC_FIELD_BUFFER];
	char	*env_var;

	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != '"')
	{
		if (p->u_input[p->inp_i] == '$')
		{
			p->inp_i++;
			if (p->u_input[p->inp_i] == ' ' || p->u_input[p->inp_i] == '"')
			{
				assignment_buffer[(*ass_buff_i)++] = '$';
				continue ;
			}
			fill_buffer(env_key_buffer, PROC_FIELD_BUFFER,
									p->u_input, &(p->inp_i));
			env_var = getenv(env_key_buffer);
			if (env_var != NULL)
			{
				ft_strlcat(assignment_buffer, env_var, PROC_FIELD_BUFFER);
				*ass_buff_i += ft_strlen(env_var);
			}
		}
		else
			assignment_buffer[(*ass_buff_i)++] = p->u_input[p->inp_i++];
	}
}

static void	parse_assignment(t_parsing *p, char *assignment_buffer,
								size_t *ass_buff_i)
{
	char	env_key_buffer[PROC_FIELD_BUFFER];
	char	*env_var;

	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ')
	{
		if (p->u_input[p->inp_i] == '$' && p->inp_i++)
		{
			if (p->u_input[p->inp_i] == ' ')
			{
				assignment_buffer[(*ass_buff_i)++] = '$';
				break ;
			}
			fill_buffer(env_key_buffer, PROC_FIELD_BUFFER,
									p->u_input, &(p->inp_i));
			env_var = getenv(env_key_buffer);
			if (env_var != NULL)
			{
				ft_strlcat(assignment_buffer, env_var, PROC_FIELD_BUFFER);
				*ass_buff_i += ft_strlen(env_var);
			}
			break ;
		}
		else
			assignment_buffer[(*ass_buff_i)++] = p->u_input[p->inp_i++];
	}
}

void	parse_env_assignment(t_parsing *p, char *buffer, size_t *buffer_i)
{
	buffer[(*buffer_i)++] = p->u_input[p->inp_i++];
	if (p->u_input[p->inp_i] == 39)  // value in single quotes -> parse as chars
	{
		p->inp_i++;
		while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' '
				&& p->u_input[p->inp_i] != 39)
			buffer[(*buffer_i)++] = p->u_input[p->inp_i++];
		p->inp_i++;
	}
	else if (p->u_input[p->inp_i] == '"')  // value in double quotes -> parse env vars
	{
		p->inp_i++;
		parse_dq_assignment(p, buffer, buffer_i);
		p->inp_i++;
	}
	else if (ft_isalnum(p->u_input[p->inp_i]) || p->u_input[p->inp_i] == '$')  // value without quotes
		parse_assignment(p, buffer, buffer_i);
}
