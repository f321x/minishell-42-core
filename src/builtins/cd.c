/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:16:14 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 14:51:51 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	char	*argv[3];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (false);
	pwd = ft_strjoin("PWD=", cwd);
	if (pwd == NULL)
		return (false);
	argv[0] = ft_strdup("export");
	argv[1] = pwd;
	argv[2] = NULL;
	if (! export(argv))
		return (false);
	return (true);
}

/*
cd works with relative paths.
*/
bool	cd(char **argv)
{
	int		error;
	char	*entered_path_arg;

	entered_path_arg = argv[1];
	if (argv[1] != NULL && argv[2] != NULL)
	{
		write(2, "cd: string not in pwd: ", 23);
		write(2, argv[1], ft_strlen(argv[1]));
		return (false);
	}
	if (entered_path_arg == NULL)
		entered_path_arg = getenv("HOME");
	if (entered_path_arg == NULL)
		return (error_wrapper());
	error = chdir(entered_path_arg);
	if (error == -1)
		return (error_wrapper());
	if (! set_pwd())
		return (error_wrapper());
	return (true);
}
