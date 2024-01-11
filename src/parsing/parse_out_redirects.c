/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_out_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:44:42 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/11 16:49:27 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_out_name(t_parsing *p, t_inoutfiles *curr_iof)
{
	char	buffer[PROC_FIELD_BUFFER];
	size_t	buffer_i;
	bool	success;

	buffer_i = 0;
	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	success = true;
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ' && success)
	{
		if (p->u_input[p->inp_i] == '$')
			fill_env_in_buffer(p, buffer, &buffer_i);
		else if (p->u_input[p->inp_i] == 39)
			success = parse_single_quote(p, buffer, &buffer_i);
		else if (p->u_input[p->inp_i] == '"')
			success = parse_double_quote(p, buffer, &buffer_i);
		else
			buffer[buffer_i++] = p->u_input[p->inp_i++];
	}
	if (ft_strlen(buffer) < 1 || !success)
		return (false);
	curr_iof->name = ft_strdup(buffer);
	p->task->processes[p->task->p_amount].io_amount++;
	if (!curr_iof->name)
		return (false);
	return (true);
}

bool	parse_out_redirect(t_parsing *p)
{
	t_process		*current_process;
	t_inoutfiles	*curr_iof;

	current_process = &(p->task->processes[p->task->p_amount]);
	curr_iof = &(current_process->iofiles[current_process->io_amount]);
	p->inp_i++;
	if (p->u_input[p->inp_i] == '>')
	{
		p->inp_i++;
		curr_iof->type = APPEND;
	}
	else if (p->u_input[p->inp_i])
		curr_iof->type = OUT;
	skip_whitespace(p);
	return (parse_out_name(p, curr_iof));
}
