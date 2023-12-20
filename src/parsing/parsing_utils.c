/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:34:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 17:52:30 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **append_string(char **orig, char *str)
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

bool	ft_isdelimiter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 39 || c == '"' || c == ' ')
		return (true);
	return (false);
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
