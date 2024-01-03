/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:10:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 14:34:31 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parsing_data(t_parsing *data, t_pipe *task, char *input)
{
	task->processes[task->p_amount].argv = NULL;
	data->inp_i = 0;
	data->buffer_i = 0;
	data->new_proc = true;
	data->task = task;
	data->u_input = input;
	// ft_memset(data->buffer, '\0', PROC_FIELD_BUFFER);
}

void	skip_whitespace(t_parsing *p)
{
	while (p && p->u_input &&
			p->u_input[p->inp_i] == ' ')
	{
		p->inp_i++;
	}
}

void	free_all_argvs(t_parsing *p)
{
	t_process 	*processes;
	long		index;

	processes = p->task->processes;
	while (p->task->p_amount > 0)
	{
		index = 0;
		while (processes && processes->argv[index] != NULL)
			index++;
		while (index >= 0)
		{
			free(processes->argv[index]);
			index--;
		}
		free(processes->argv);
		p->task->p_amount--;
	}
}
