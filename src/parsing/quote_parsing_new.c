/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:50:48 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/12 14:17:41 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_buffer_to_argv(t_parsing *p, char *buffer)
{
	t_process	*curr_proc;

	curr_proc = &(p->task->processes[p->task->p_amount]);
	if (ft_strlen(buffer) > 0)
	{
		curr_proc->argv = append_string(curr_proc->argv, buffer);
		if (!curr_proc->argv)
			return (false);
	}
	return (true);
}

bool	parse_single_quote(t_parsing *p, char *buffer, size_t *buffer_i)
{
	p->inp_i++;
	skip_whitespace(p);
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != 39)
		buffer[(*buffer_i)++] = p->u_input[(p->inp_i)++];
	if (p->u_input[p->inp_i] != 39)
		return (false);
	p->inp_i++;
	return (true);
}

void	fill_env_in_buffer(t_parsing *p, char *buffer, size_t *buffer_i)
{
	char		env_buffer[PROC_FIELD_BUFFER];
	char		*env_var;

	p->inp_i++;
	if (!ft_isalnum(p->u_input[p->inp_i]))
	{
		buffer[(*buffer_i)++] = '$';
		return ;
	}
	fill_buffer(env_buffer, PROC_FIELD_BUFFER, p);
	env_var = getenv(env_buffer);
	if (env_var != NULL)
	{
		ft_strlcat(buffer, env_var, PROC_FIELD_BUFFER);
		*buffer_i += ft_strlen(env_var);
	}
}

bool	parse_double_quote(t_parsing *p, char *buffer, size_t *buffer_i)
{
	p->inp_i++;
	skip_whitespace(p);
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != '"')
	{
		if (p->u_input[p->inp_i] == '$')
			fill_env_in_buffer(p, buffer, buffer_i);
		else
			buffer[(*buffer_i)++] = p->u_input[(p->inp_i)++];
	}
	if (p->u_input[p->inp_i] != '"')
		return (false);
	p->inp_i++;
	return (true);
}

bool	parse_remaining(t_parsing *p)
{
	char	buffer[PROC_FIELD_BUFFER];
	// size_t	buffer_i;


	if (!fill_buffer(buffer, PROC_FIELD_BUFFER, p))
		return (false);
	if (!add_buffer_to_argv(p, buffer))
		return (false);
	return (true);

	// ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	// buffer_i = 0;
	// while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ')
	// {
	// 	if (p->u_input[p->inp_i] == 39)
	// 	{
	// 		if (!parse_single_quote(p, buffer, &buffer_i))
	// 			return (false);
	// 	}
	// 	else if (p->u_input[p->inp_i] == '"')
	// 	{
	// 		if (!parse_double_quote(p, buffer, &buffer_i))
	// 			return (false);
	// 	}
	// 	else if (p->u_input[p->inp_i] == '$')
	// 		fill_env_in_buffer(p, buffer, &buffer_i);
	// 	else
	// 		buffer[buffer_i++] = p->u_input[p->inp_i++];
	// }

}
