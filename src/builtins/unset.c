/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:25:06 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 13:52:18 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_new_environ(char *remove_var, char **new_env,
							char **old_env, size_t env_size)
{
	size_t	new_index;
	size_t	old_index;

	new_index = 0;
	old_index = 0;
	while (old_index < env_size)
	{
		if (getenv(remove_var) - 1 - ft_strlen(remove_var)
			!= old_env[old_index])
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
	new_env[new_index] = NULL;
	return (true);
}

static bool	alloc_new_environ(size_t env_size, char *variable_name)
{
	extern char	**environ;
	char		**new_environ;
	char		**env_buffer;

	new_environ = malloc((sizeof(char *) * (env_size - 1)) + sizeof(void *));
	if (!new_environ)
		return (false);
	if (!init_new_environ(variable_name, *new_environ, environ, env_size))
	{
		free(new_environ);
		return (false);
	}
	env_buffer = environ;
	environ = new_environ;
	free_old_env(env_buffer);
	return (true);
}

bool	unset(char **argv)
{
	size_t		env_size;
	char		*variable_name;
	int			i;

	i = 1;
	while (argv[i] != NULL)
	{
		variable_name = argv[i];
		if (getenv(variable_name) == NULL)
		{
			i++;
			continue ;
		}
		env_size = get_env_length();
		if (env_size < 1)
			return (true);
		if (!alloc_new_environ(env_size, variable_name))
			return (false);
		i++;
	}
	return (true);
}
