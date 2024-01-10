/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:16:14 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 13:37:06 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (true);
}
