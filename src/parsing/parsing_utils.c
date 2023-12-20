/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:34:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 16:36:38 by ***REMOVED***            ###   ########.fr       */
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
