/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:10:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 12:34:46 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initializes the parsing struct
void	init_parsing_data(t_parsing *data, t_pipe *task, char *input)
{
	task->processes[task->p_amount].argv = NULL;
	task->processes[task->p_amount].io_amount = 0;
	data->inp_i = 0;
	data->buffer_i = 0;
	data->new_proc = true;
	data->task = task;
	data->u_input = input;
}

// function to skip whitespaces in the u_input string in the
// parsing struct. Will increase the inp_i index in the parsing struct
void	skip_whitespace(t_parsing *p)
{
	while (p && p->u_input &&
			p->u_input[p->inp_i] == ' ')
	{
		p->inp_i++;
	}
}

// frees all argv 2d arrays from the given pipe struct and all
// coming before. Called between each user input.
bool	free_all_argvs(t_pipe *task)
{
	t_process 	*processes;
	long		index;

	processes = task->processes;
	while (task->p_amount > 0)
	{
		index = 0;
		while (processes && processes->argv &&
				processes->argv[index] != NULL)
		{
			free(processes->argv[index]);
			processes->argv[index] = NULL;
			index++;
		}
		free(processes->argv);
		processes->argv = NULL;
		task->p_amount--;
		processes++;
	}
	return (false);
}

// adds a string to the argv 2d array, safe to use if
// argv has not been initialized yet and is NULL.
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
	{
		if (p->u_input[p->inp_i] == '=')
		{
			if (!parse_env_assignment(p, buffer, &buffer_i))
			{
				printf("Wrong format!\n");
				return (false);
			}
		}
		else
			buffer[buffer_i++] = p->u_input[p->inp_i++];
	}
	*current_argv = append_string(*current_argv, buffer);
	return (*current_argv);
}

// called when a pipe character is encountered in user input
// will "create" a new pipe struct by setting new_proc true and
// increasing the input index by 1 to go to the next char in u_input.
bool	handle_pipe(t_parsing *p)
{
	p->inp_i++;
	p->new_proc = true;
	return (true);
}
