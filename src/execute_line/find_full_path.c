/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_full_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:04:38 by marschul          #+#    #+#             */
/*   Updated: 2024/01/11 13:42:51 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	expand_path_var(char *paths, char new_paths[PATH_MAX])
{
	int		i;

	i = 0;
	while (*paths != '\0')
	{
		if (*paths == ':' && (*(paths + 1) == ':' || *(paths + 1) == '\0'))
		{
			new_paths[i] = ':';
			new_paths[i + 1] = '.';
			i += 1;
		}
		else
			new_paths[i] = *paths;
		i++;
		if (i >= PATH_MAX - 2)
			return (false);
		paths++;
	}
	new_paths[i] = ':';
	new_paths[i + 1] = '\0';
	return (true);
}

int	concatenate_path_with_name(char *start, char *name, \
	char full_path[12000])
{
	int		full_path_index;
	char	*end;

	full_path_index = 0;
	end = ft_strchr(start, ':');
	ft_memcpy(full_path, start, end - start);
	full_path_index += end - start;
	full_path[full_path_index] = '/';
	full_path_index++;
	ft_memcpy(full_path + full_path_index, name, ft_strlen(name));
	full_path_index += ft_strlen(name);
	full_path[full_path_index] = '\0';
	return (full_path_index - ft_strlen(name));
}

bool	check_path(t_process *process, char path[PATH_MAX])
{
	if (access(path, F_OK) == 0)
	{
		free(process->argv[0]);
		process->argv[0] = ft_strdup(path);
		return (true);
	}
	return (false);
}

bool	find_full_path(t_process *process)
{
	char	*paths;
	char	*name;
	char	full_path[12000];
	char	new_paths[1000];
	char	*start;

	paths = getenv("PATH");
	if (paths == NULL || ft_strlen(paths) == 0)
		return (true);
	name = process->argv[0];
	if (name[0] == '/' || (ft_strlen(name) >= 2 && name[0] == '.' && \
		name[1] == '/') || (ft_strlen(name) >= 3 && name[0] == '.' && \
		name[1] == '.' && name[2] == '/'))
		return (true);
	if (! expand_path_var(paths, new_paths))
		return (false);
	start = new_paths;
	while (*start != '\0')
	{
		start += concatenate_path_with_name(start, name, full_path);
		if (check_path(process, full_path))
			return (true);
	}
	return (false);
}
