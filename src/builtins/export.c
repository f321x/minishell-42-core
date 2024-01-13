/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:43:49 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/13 19:01:26 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_env_length(void)
{
	extern char	**environ;
	size_t		env_size;

	env_size = 0;
	while (environ && environ[env_size] != NULL)
		env_size++;
	return (env_size);
}

// first time is system memory and can't be freed, 2nd+ is self allocated.
void	free_old_env(char **old_env)
{
	size_t			index;
	extern char		**environ;
	static bool		called_before = false;

	index = 0;
	if (old_env == NULL)
		old_env = environ;
	if (called_before)
		free_vector(old_env);
	called_before = true;
}

// call for each pair of variable=value to export it to the env
bool	export_one_pair(char *env_pair)
{
	extern char	**environ;
	char		**old_env_buffer;
	char		**new_environ;
	size_t		env_size;

	env_size = get_env_length();
	if (env_size < 1)
		return (false);
	new_environ = malloc((sizeof(char *) * (env_size + 1)) + sizeof(void *));
	if (!new_environ)
		return (false);
	if (!set_new_environ(env_pair, new_environ, environ, env_size))
	{
		free(new_environ);
		return (false);
	}
	old_env_buffer = environ;
	environ = new_environ;
	free_old_env(old_env_buffer);
	return (true);
}

bool	export(char **argv)
{
	int		i;
	char	*key;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		key = ft_strdup(argv[i]);
		if (key == NULL)
			return (false);
		*(ft_strchr(key, '=')) = '\0';
		if (getenv(key) != NULL)
		{
			if (!(set_false_argv_for_unset(key)))
				return (false);
		}
		free(key);
		if (!export_one_pair(argv[i++]))
			return (false);
	}
	return (true);
}
