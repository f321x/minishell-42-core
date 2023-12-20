/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:16:14 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 15:58:24 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns absolute path
bool	cd(char **argv)
{
	int		error;
	char	*entered_path_arg;

	entered_path_arg = argv[1];
	if (entered_path_arg == NULL)
		entered_path_arg = getenv("HOME");
	if (entered_path_arg == NULL)
		return (false);
	error = chdir(entered_path_arg);
	if (error == -1)
	{
		perror("Error changing directory.");
		return (false);
	}
	return (true);
}
