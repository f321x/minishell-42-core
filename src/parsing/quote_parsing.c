/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:50:48 by fbock             #+#    #+#             */
/*   Updated: 2024/01/08 13:42:10 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_single_quote(t_parsing *p)
{
	char		buffer[PROC_FIELD_BUFFER];
	size_t		buffer_i;
	t_process	*curr_proc;

	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	buffer_i = 0;
	curr_proc = &(p->task->processes[p->task->p_amount]);
	p->inp_i++;
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != 39)
		buffer[buffer_i++] = p->u_input[(p->inp_i)++];
	if (p->u_input[p->inp_i] != 39)
		return (false);
	if (buffer_i > 0)
	{
		curr_proc->argv = append_string(curr_proc->argv, buffer);
		if (!curr_proc->argv)
			return (false);
	}
	p->inp_i++;
	return (true);
}

void fill_env_in_buffer(t_parsing *p, char *buffer, size_t *buffer_i)
{
	char		env_buffer[PROC_FIELD_BUFFER];
	char		*env_var;

	p->inp_i++;
	if (!ft_isalnum(p->u_input[p->inp_i]))
	{
		buffer[(*buffer_i)++] = '$';
		return ;
	}
	fill_buffer(env_buffer, PROC_FIELD_BUFFER,
							p->u_input, &(p->inp_i));
	env_var = getenv(env_buffer);
	if (env_var != NULL)
	{
		ft_strlcat(buffer, env_var, PROC_FIELD_BUFFER);
		*buffer_i += ft_strlen(env_var);
	}
}

bool	parse_double_quote(t_parsing *p)
{
	char		buffer[PROC_FIELD_BUFFER];
	t_process	*curr_proc;
	size_t		buffer_i;

	buffer_i = 0;
	curr_proc = &(p->task->processes[p->task->p_amount]);
	p->inp_i++;
	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != '"')
	{
		if (p->u_input[p->inp_i] == '$')
			fill_env_in_buffer(p, buffer, &buffer_i);
		else
			buffer[buffer_i++] = p->u_input[(p->inp_i)++];
	}
	if (p->u_input[p->inp_i] != '"')
		return (false);
	if (buffer_i > 0)
	{
		curr_proc->argv = append_string(curr_proc->argv, buffer);
		if (!curr_proc->argv)
			return (false);
	}
	p->inp_i++;
	return (true);
}
