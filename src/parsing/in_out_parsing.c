/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:08:19 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/23 14:14:23 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_infile(t_parsing *pd)
{
	pd->buffer_i = 0;
	pd->buffer[0] = '\0';
	pd->line_i++;
	while (pd->entered_line[pd->line_i] == ' ')
		(pd->line_i)++;
	while (pd->entered_line[pd->line_i] && !ft_isdelimiter(pd->entered_line[pd->line_i]))
	{
		pd->buffer[pd->buffer_i] = pd->entered_line[pd->line_i];
		(pd->line_i)++;
	}
	pd->buffer[pd->buffer_i] = '\0';
	pd->task->input_file = ft_strdup(pd->buffer);
	if (!pd->task->input_file)
		return (false);
	return (true);
}

bool	parse_outfile(t_parsing *pd)
{
	pd->buffer_i = 0;
	pd->buffer[0] = '\0';
	pd->line_i++;
	if (pd->entered_line[pd->line_i] == '>')
		return (parse_heredoc(pd));
	while (pd->entered_line[pd->line_i] == ' ')
		(pd->line_i)++;
	while (pd->entered_line[pd->line_i] && !ft_isdelimiter(pd->entered_line[pd->line_i]))
	{
		pd->buffer[pd->buffer_i] = pd->entered_line[pd->line_i];
		(pd->line_i)++;
	}
	pd->buffer[pd->buffer_i] = '\0';
	pd->task->output_file = ft_strdup(pd->buffer);
	if (!pd->task->output_file)
		return (false);
	return (true);
}

bool	parse_heredoc(t_parsing *pd)
{
	char	*prev_res;
	char 	*result;
	char	*in_buffer;

	pd->buffer_i = 0;
	pd->buffer[0] = '\0';
	pd->line_i++;
	prev_res = NULL;
	while (pd->entered_line[pd->line_i] == ' ')
		(pd->line_i)++;
	while (pd->entered_line[pd->line_i] && !ft_isdelimiter(pd->entered_line[pd->line_i]))
	{
		pd->buffer[pd->buffer_i] = pd->entered_line[pd->line_i];
		pd->buffer_i++;
		(pd->line_i)++;
	}
	pd->buffer[pd->buffer_i] = '\0';
	while (1)
	{
		in_buffer = readline("heredoc> ");
		if (!in_buffer)
		{
			if (prev_res)
				free(prev_res);
			if (result)
				free(result);
			return (false);
		}
		result = ft_strjoin(prev_res, in_buffer);
		if (!result)
		{
			free(in_buffer);
			if (prev_res)
				free(prev_res);
			return (false);
		}
		if (prev_res)
			free(prev_res);
		prev_res = result;
		if (!ft_strcmp(in_buffer, pd->buffer))
		{
			free(in_buffer);
			break;
		}
		free(in_buffer);
	}
	pd->task->here_file = result;
	return (true);
}
