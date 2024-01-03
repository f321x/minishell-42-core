/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:40:15 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 15:00:04 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_name(t_parsing *p)
{
	char 		buffer[PROC_FIELD_BUFFER];
	size_t		index;
	t_process	*curr_proc;

	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	index = 0;
	curr_proc = &(p->task->processes[p->task->p_amount]);
	while (!ft_isdelimiter(p->u_input[p->inp_i]))
	{
		buffer[index] = p->u_input[p->inp_i];
		p->inp_i++;
		index++;
	}
	if (index > 0)
	{
		curr_proc->argv = append_string(curr_proc->argv, buffer);
		if (!curr_proc->argv)
		{
			free_all_argvs(p);
			return (false);
		}
	}
	p->new_proc = false;
	return (true);
}

bool	parse_delimiter(t_parsing *p)
{
	if (!(p->u_input))
}
