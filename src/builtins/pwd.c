/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:31:48 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/21 20:25:06 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pwd(char **argv)
{
	char	buffer[CWD_BUFFER_SIZE];
	char	*getcwd_retv;
	int		error;

	if (argv[1] != NULL)
	{
		write(2, "pwd: too many arguments", 23);
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
