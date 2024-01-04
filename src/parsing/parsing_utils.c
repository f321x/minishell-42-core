/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:10:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/04 12:57:28 by ***REMOVED***            ###   ########.fr       */
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

bool	free_all_argvs(t_parsing *p)
{
	t_process 	*processes;
	long		index;

	processes = p->task->processes;
	while (p->task->p_amount > 0)
	{
		index = 0;
		while (processes && processes->argv &&
				processes->argv[index] != NULL)
		{
			printf("index %ld\n", index);
			free(processes->argv[index]);
			index++;
		}
		free(processes->argv);
		p->task->p_amount--;
		processes++;
	}
	return (false);
}

bool	add_to_argv(t_parsing *p)
{
	char	***current_argv;
	char	buffer[PROC_FIELD_BUFFER];
	size_t	buffer_i;

	current_argv = &(p->task->processes[p->task->p_amount].argv);
	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	buffer_i = 0;
	buffer[buffer_i++] = p->u_input[(p->inp_i)++];
	while (p->u_input && p->u_input[p->inp_i]
			&& !ft_isdelimiter(p->u_input[p->inp_i]))
		buffer[buffer_i++] = p->u_input[p->inp_i++];
	*current_argv = append_string(*current_argv, buffer);
	if (!(*current_argv))
		return (false);
	return (true);
}

bool	handle_pipe(t_parsing *p)
{
	p->inp_i++;
	p->new_proc = true;
	return (true);
}
