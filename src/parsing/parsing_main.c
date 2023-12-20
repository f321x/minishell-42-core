/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:38:28 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 16:14:25 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	isolate_name(char *entered_line, int *line_i, char *buffer)
{
	size_t	buffer_i;

	buffer_i = 0;
	while (entered_line[*line_i] && !ft_isdelimiter(entered_line[*line_i]))
	{
		buffer[buffer_i] = entered_line[*line_i];
		buffer_i++;
		(*line_i)++;
	}
	buffer[buffer_i] = '\0';
}

static void	check_rest(char *entered_line, int *line_i, t_pipe *task)
{
	if (entered_line[line_i] == ' ')

	else if (entered_line[line_i] == 39)

	else if (entered_line[line_i] == '"')

	return (false);
}

bool	parse_line(char *entered_line, t_pipe *task)
{
	char	buffer[PROC_FIELD_BUFFER];
	size_t	line_i;
	bool	new_proc;

	line_i = 0;
	new_proc = true;
	while (entered_line && entered_line[line_i])
	{
		// isolate name
		if (new_proc)
		{
			isolate_name(entered_line, &line_i, buffer);
			new_proc = false;
			task->processes[task->p_amount].name = ft_strdup(buffer);
		}
		if (entered_line[line_i] == '|')
		{
			//
			new_proc = true;
		}
		else
		{
			check_rest(entered_line, line_i, task);
		}
	}

}
