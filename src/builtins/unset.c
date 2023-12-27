/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:25:06 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/27 21:06:47 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_new_environ(char *remove_var, char **new_env,
							char **old_env, size_t env_size)
{
	long	new_index;
	long	old_index;

	new_index = 0;
	old_index = 0;
	while (old_index < env_size)
	{
		if (getenv(remove_var) - 1 - ft_strlen(remove_var) != old_env[old_index])
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

bool	unset(char **argv)
{
	size_t		env_size;
	extern char	**environ;
	char		**new_environ;
	char		**env_buffer;
	char		*variable_name;
	int			i;

	assert(argv != NULL && ft_strcmp(argv[0], "unset") == 0); // debug

	if (argv[1] == NULL)
	{
		write(2, "unset: not enough arguments\n", 28);
		return (false);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		variable_name = argv[i];
		if (getenv(variable_name) == NULL)
		{
			i++;
			continue;
		}
		env_size = get_env_length();
		if (env_size < 1)
			return (true);
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
		i++;
	}
	return (true);
}
