/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:50:48 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/04 11:56:58 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_single_quote(t_parsing *p)
{
	char		buffer[PROC_FIELD_BUFFER];
	size_t		index;
	t_process	*curr_proc;

	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	index = 0;
	curr_proc = &(p->task->processes[p->task->p_amount]);
	p->inp_i++;
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != 39)
		buffer[index++] = p->u_input[(p->inp_i)++];
	if (p->u_input[p->inp_i] != 39)
		return (false);
	if (index > 0)
	{
		curr_proc->argv = append_string(curr_proc->argv, buffer);
		if (!curr_proc->argv)
			return (false);
	}
	p->inp_i++;
	return (true);
}
