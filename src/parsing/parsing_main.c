/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 11:17:10 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*alloc_proc(char *name, char **argv)
{
	t_process	*proc;

	proc = malloc(sizeof(t_process));
	if (!proc)
		return (NULL);
	proc->name = malloc((ft_strlen(name) + 1) * sizeof(char));
	if (!proc->name)
	{
		free(proc);
		return (NULL);
	}
	proc->name = name;
	return (proc);
	// argv tbd
}

bool	ft_isdelimiter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 39 || c == '"' || c == ' ')
		return (true);
	return (false);
}

// void	parse_delimiter(char **rem_tokens, t_pipe *task)
// {
// 	char	before_buffer[1000];
// 	char	after_buffer[1000];
// 	size_t	index = 0;

// 	while (**rem_tokens && !ft_isdelimiter(**rem_tokens))
// 	{
// 		before_buffer[index] = **rem_tokens;
// 		(*rem_tokens)++;
// 	}

// }



// non functional prototype
bool	parse_line(char *entered_line, t_pipe *task)
{
	char		name_buf[PROC_FIELD_BUFFER];
	char		argv_buf[PROC_FIELD_BUFFER];
	// size_t		proc_i;
	size_t		buf_i;
	size_t		line_i;

	// proc_i = 0;
	buf_i = 0;
	line_i = 0;
	while (entered_line && entered_line[line_i])
	{
		while (!ft_isdelimiter(entered_line[line_i]) && buf_i < PROC_FIELD_BUFFER)
		{
			name_buf[buf_i] = entered_line[line_i];
			buf_i++;
			line_i++;
		}
		name_buf[buf_i] = '\0';
		task->processes[task->p_amount].name = ft_strdup(name_buf);

		if (entered_line[line_i] == ' ')
		{
			line_i++;
			buf_i = 0;
			while (!ft_isdelimiter(entered_line[line_i]))
			{
				argv_buf[buf_i] = entered_line[line_i];
				buf_i++;
				line_i++;
			}

		}
		else if (entered_line[line_i] == '')
	}
	return (true);
}

// bool	check_builtin(t_parsing *input)
// {
// 	if (ft_strcmp(*(input->tokens), "cd") == 0)
// 		cd(*(++input->tokens));
// 	else if (ft_strcmp(string, "echo") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "env") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "export") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "pwd") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "unset") == 0)
// 	{

// 	}
// 	return (false);
// }
