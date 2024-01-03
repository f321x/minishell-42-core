/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:10:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 12:04:00 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parsing_data(t_parsing *data, t_pipe *task, char *input)
{
	task->processes[task->p_amount].argv = NULL;
	data->line_i = 0;
	data->buffer_i = 0;
	data->new_proc = true;
	data->task = task;
	data->u_input = input;
	ft_memset(data->buffer, '\0', PROC_FIELD_BUFFER);
}
