/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:06:47 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/13 18:31:42 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	copy_old_env(char **old_env, char **new_env, size_t env_size)
{
	size_t	index;

	index = 0;
	while (index < env_size)
	{
		new_env[index] = ft_strdup(old_env[index]);
		if (!new_env[index])
		{
			index--;
			while (index > 0)
			{
				free(new_env[index]);
				index--;
			}
			return (false);
		}
		index++;
	}
	return (true);
}

bool	set_new_environ(char *new_pair, char **new_environ,
								char **old_environ, size_t size)
{
	char	*new_env_var_heap;

	new_env_var_heap = ft_strdup(new_pair);
	if (!new_env_var_heap)
	{
		free(new_environ);
		return (false);
	}
	if (!copy_old_env(old_environ, new_environ, size))
	{
		free(new_env_var_heap);
		return (false);
	}
	new_environ[size] = new_env_var_heap;
	new_environ[size + 1] = NULL;
	return (true);
}

bool	set_false_argv_for_unset(char *key)
{
	char	*false_argv_for_unset[3];

	false_argv_for_unset[0] = "unset";
	false_argv_for_unset[1] = key;
	false_argv_for_unset[2] = NULL;
	if (!unset(false_argv_for_unset))
		return (false);
	return (true);
}
