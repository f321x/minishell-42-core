/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:16:14 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/21 20:05:22 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns absolute path
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
	return (true);
}
