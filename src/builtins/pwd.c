/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:31:48 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/27 12:19:57 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pwd(char **argv)
{
	char	buffer[CWD_BUFFER_SIZE];
	char	*getcwd_retv;
	int		error;

	assert(argv != NULL && ft_strcmp(argv[0], "pwd") == 0); // debug

	if (argv[1] != NULL)
	{
		write(2, "pwd: too many arguments\n", 24);
		return (false);
	}
	getcwd_retv = getcwd(buffer, CWD_BUFFER_SIZE);
	if (getcwd_retv == NULL)
		return (error_wrapper());
	error = ft_printf("%s\n", buffer);
	if (error < 0)
		return (error_wrapper());
	return (true);
}
