/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:25:06 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 19:45:54 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_new_environ(char *remove_var, char **old_env,
							char **new_env, size_t env_size)
{
	long	new_index;
	long	old_index;

	new_index = 0;
	old_index = 0;
	while (old_index < env_size)
	{
		if (ft_strncmp(old_env[old_index], remove_var, ft_strlen(remove_var)))
		{
			new_env[new_index] = ft_strdup(old_env[old_index]);
			if (!new_env[new_index])
			{
				new_index--;
				while (new_index > 0)
					free(new_env[new_index--]);
				return (false);
			}
			new_index++;
		}
		old_index++;
	}
	return (true);
}

bool	unset(char *variable_name)
{
	size_t		env_size;
	extern char	**environ;
	char		**new_environ;
	char		**env_buffer;

	env_size = get_env_length();
	if (env_size < 1)
		return (false);
	new_environ = malloc((sizeof(char *) * (env_size - 1)) + sizeof(void *));
	if (!new_environ)
		return (false);
	if (!init_new_environ(variable_name, new_environ, environ, env_size))
	{
		free(new_environ);
		return (false);
	}
	env_buffer = environ;
	environ = new_environ;
	free_old_env(env_buffer);
	return (true);
}
