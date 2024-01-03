/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:38:28 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 11:29:43 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	isolate_name(t_parsing *pd)
{
	pd->buffer_i = 0;
	pd->buffer[0] = '\0';
	while (pd->entered_line[pd->line_i] && !ft_isdelimiter(pd->entered_line[pd->line_i]))
	{
		pd->buffer[pd->buffer_i] = pd->entered_line[pd->line_i];
		pd->buffer_i++;
		(pd->line_i)++;
	}
	pd->buffer[pd->buffer_i] = '\0';
}

void	parse_quote(t_parsing *pd)
{
	pd->buffer_i = 0;
	pd->buffer[0] = '\0';
	if (pd->entered_line[pd->line_i] == 39)
	{
		(pd->line_i)++;
		while (pd->entered_line[pd->line_i] && pd->entered_line[pd->line_i] != 39)
		{
			pd->buffer[pd->buffer_i++] = pd->entered_line[pd->line_i];
			(pd->line_i)++;
		}
		pd->buffer[pd->buffer_i] = '\0';
		if (ft_strlen(pd->buffer) > 0)
			pd->task->processes[pd->task->p_amount].argv = append_string(pd->task->processes[pd->task->p_amount].argv, pd->buffer);
	}
	else if (pd->entered_line[pd->line_i] == '"')
	{
		(pd->line_i)++;
		while (pd->entered_line[pd->line_i] && pd->entered_line[pd->line_i] != '"')
		{
			if (pd->entered_line[pd->line_i] == '$')
				parse_placeholder(pd);
			else
			{
				pd->buffer[pd->buffer_i++] = pd->entered_line[pd->line_i];
				(pd->line_i)++;
			}
		}
		pd->buffer[pd->buffer_i] = '\0';
		if (ft_strlen(pd->buffer) > 0)
			pd->task->processes[pd->task->p_amount].argv = append_string(pd->task->processes[pd->task->p_amount].argv, pd->buffer);
	}
}

static void	check_rest(t_parsing *pd)
{
	pd->buffer_i = 0;
	pd->buffer[0] = '\0';
	if (pd->entered_line[pd->line_i] == ' ')
	{
		pd->line_i++;
		while (!ft_isdelimiter(pd->entered_line[pd->line_i]) && pd->entered_line[pd->line_i])
		{
			if (pd->entered_line[pd->line_i] == '$')
				parse_placeholder(pd);
			else
			{
				pd->buffer[pd->buffer_i++] = pd->entered_line[pd->line_i];
				pd->line_i++;
			}
		}
		pd->buffer[pd->buffer_i] = '\0';
		if (ft_strlen(pd->buffer) > 0)
			pd->task->processes[pd->task->p_amount].argv = append_string(pd->task->processes[pd->task->p_amount].argv, pd->buffer);
	}
	else if (pd->entered_line[pd->line_i] == 39 || pd->entered_line[pd->line_i] == '"')
		parse_quote(pd);
	else if (pd->entered_line[pd->line_i] == '$')
		parse_placeholder(pd);
	else if (pd->entered_line[pd->line_i] == '<')
		parse_infile(pd);
	else if (pd->entered_line[pd->line_i] == '>')
		parse_outfile(pd);
	// return (false);
}

bool	parse_line(char *entered_line, t_pipe *task)
{
	t_parsing pd;
	extern char **environ;

	pd.line_i = 0;
	pd.new_proc = true;
	pd.entered_line = entered_line;
	pd.task = task;
	pd.task->processes[task->p_amount].argv = NULL;
	pd.task->processes[task->p_amount].env = environ;
	while (entered_line && entered_line[pd.line_i])
	{
		// isolate name
		if (pd.new_proc)
		{
			// printf("NEW PROC CALLED\n");
			isolate_name(&pd);
			pd.new_proc = false;
			task->processes[task->p_amount].name = ft_strdup(pd.buffer);
			// printf("process %s\n", task->processes[task->p_amount].name);
		}
		if (entered_line[pd.line_i] == '|')
		{
			// printf("PIPE CALLED\n");
			pd.new_proc = true;
			(pd.line_i)++;
			while (entered_line[pd.line_i] == ' ')
				(pd.line_i)++;
			(task->p_amount)++;
		}
		else if (entered_line[pd.line_i])
		{
			check_rest(&pd);
		}
	}
	(task->p_amount)++;
	return (true);
}

// typedef struct s_parsing {
// 	char	buffer[PROC_FIELD_BUFFER];
// 	char	*entered_line;
// 	size_t	line_i;
// 	size_t	buffer_i;
// 	bool	new_proc;
// 	t_pipe	*task;
// }	t_parsing;
