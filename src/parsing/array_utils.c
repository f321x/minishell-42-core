/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:18:02 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 12:40:33 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**alloc_new_arr(char **original, size_t *amount)
{
	*amount = 0;
	while (original && original[*amount])
		(*amount)++;
	return (malloc((sizeof(char *) * *amount) + sizeof(void *)
			+ sizeof(char *)));
}

static void	*free_on_error(char **to_free, int from_index)
{
	while (from_index > 0)
	{
		from_index--;
		free(to_free[from_index]);
	}
	free(to_free);
	return (NULL);
}

char	**append_string(char **orig, char *str)
{
	size_t	amount;
	long	index;
	char	**new_str_arr;

	index = 0;
	new_str_arr = alloc_new_arr(orig, &amount);
	if (!new_str_arr)
		return (NULL);
	while (index < amount)
	{
		new_str_arr[index] = orig[index];
		index++;
	}
	new_str_arr[index] = ft_strdup(str);
	if (!new_str_arr[index])
		return (free_on_error(new_str_arr, index));
	new_str_arr[index + 1] = NULL;
	if (amount > 0)
		free(orig);
	return (new_str_arr);
}
