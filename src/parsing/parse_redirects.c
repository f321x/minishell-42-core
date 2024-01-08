/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:44:42 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/08 12:07:49 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	parse_in_redirect(t_parsing *p)
// {
// 	t_process		*current_process;
// 	t_inoutfiles	*curr_iof;

// 	current_process = &(p->task->processes[p->task->p_amount]);
// 	curr_iof = &(current_process->iofiles[current_process->io_amount]);
// 	p->inp_i++;
// 	if (p->u_input[p->inp_i] == '<')
// 	{
// 		p->inp_i++;
// 		curr_iof->type = HEREDOC;
// 	}
// 	else if (p->u_input[p->inp_i])
// 		curr_iof->type = IN;
// 	skip_whitespace(p);
// 	if (!ft_isdelimiter(p->u_input[p->inp_i]))
// 		return (parse_in_name(p, curr_iof));
// 	return (false);
// }

static bool	parse_out_name(t_parsing *p, t_inoutfiles *curr_iof)
{
	size_t	name_l;
	size_t	buff_i;
	size_t	name_i;

	buff_i = p->inp_i;
	name_i = 0;
	while (p->u_input[buff_i] && !ft_isdelimiter(p->u_input[buff_i]))
		buff_i++;
	if (buff_i > p->inp_i)
		curr_iof->name = ft_calloc((buff_i - p->inp_i) + 1, sizeof(char));
	else
		return (false);
	if (!curr_iof->name)
		return (false);
	while (buff_i > p->inp_i)
		curr_iof->name[name_i++] = p->u_input[p->inp_i++];
	p->task->processes[p->task->p_amount].io_amount++;
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
	if (!ft_isdelimiter(p->u_input[p->inp_i]))
		return (parse_out_name(p, curr_iof));
	return (false);
}
