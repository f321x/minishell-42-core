/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 14:24:34 by ***REMOVED***            ###   ########.fr       */
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

static char **append_string(char **orig, char *str)
{
	size_t	amount;
	long	index;
	char	**new_str_arr;

	amount = 0;
	index = 0;
	while (orig && orig[amount] != NULL)
		amount++;
	new_str_arr = malloc(((sizeof(char *) + 1) * amount) + sizeof(void *));
	if (!new_str_arr)
		return (NULL);
	while (index < amount)
	{
		new_str_arr[index] = orig[index];
		index++;
	}
	new_str_arr[index] = ft_strdup(str);
	if (!new_str_arr[index])
	{
		while (index > 0)
		{
			free(new_str_arr[index]);
			index--;
		}
		free(new_str_arr);
		return (NULL);
	}
	new_str_arr[index + 1] = NULL;
	free(orig);
	return (new_str_arr);
}

void	parse_placeholder(char *entered_line, size_t *line_i, size_t *buf_i, char *argv_buf)
{
	char	*env_var;
	char	*env_value;
	char	*env_var_name;
	size_t	env_var_name_len;

	(*line_i)++;
	(*buf_i)++;
	env_var_name_len = 0;
	while (ft_isalnum(entered_line[*line_i + env_var_name_len]))
		env_var_name_len++;
	env_var_name = malloc(env_var_name_len + 1);
	if (!env_var_name)
		return ;
	env_var_name[env_var_name_len] = '\0';
	env_var_name_len = 0;
	while (ft_isalnum(entered_line[*line_i]))
	{
		env_var_name[env_var_name_len] = entered_line[*line_i];
		env_var_name_len++;
		(*line_i)++;
	}
	env_var = getenv(env_var_name);
	if (!env_var)
		env_value = "";
	else
		env_value = env_var;
	while (*env_value)
	{
		argv_buf[*buf_i] = *env_value;
		(*buf_i)++;
		env_value++;
	}
	free(env_var_name);
}

// non functional prototype
bool	parse_line(char *entered_line, t_pipe *task)
{
	char		name_buf[PROC_FIELD_BUFFER];
	char		argv_buf[PROC_FIELD_BUFFER];
	// size_t		proc_i;
	size_t		buf_i;
	size_t		line_i;
	size_t		argv_i;

	// proc_i = 0;
	buf_i = 0;
	line_i = 0;
	argv_i = 0;
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
			while (!ft_isdelimiter(entered_line[line_i]) && entered_line[line_i])
			{
				argv_buf[buf_i] = entered_line[line_i];
				buf_i++;
				line_i++;
			}
			argv_buf[buf_i] = '\0';
			task->processes[task->p_amount].argv = append_string(task->processes[task->p_amount].argv, argv_buf);
		}
		else if (entered_line[line_i] == 39)
		{
			line_i++;
			buf_i = 0;
			while (entered_line[line_i] != 39 && entered_line[line_i])
			{
				argv_buf[buf_i] = entered_line[line_i];
				buf_i++;
				line_i++;
			}
			argv_buf[buf_i] = '\0';
			task->processes[task->p_amount].argv = append_string(task->processes[task->p_amount].argv, argv_buf);
		}

		else if (entered_line[line_i] == '"')
		{
			line_i++;
			buf_i = 0;
			while (entered_line[line_i] != '"' && entered_line[line_i])
			{
				if (entered_line[line_i] == '$')
				{
					parse_placeholder(entered_line, &line_i, &buf_i, argv_buf);
				}
				else
				{
					argv_buf[buf_i] = entered_line[line_i];
					buf_i++;
					line_i++;
				}
			}
			argv_buf[buf_i] = '\0';
			task->processes[task->p_amount].argv = append_string(task->processes[task->p_amount].argv, argv_buf);
		}
		else if (entered_line[line_i] == '|')
		{
			line_i++;
			buf_i = 0;
			task->p_amount++;
		}
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
