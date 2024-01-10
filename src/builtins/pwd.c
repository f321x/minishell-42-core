/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:31:48 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 13:46:19 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pwd(char **argv)
{
	char	buffer[CWD_BUFFER_SIZE];
	char	*getcwd_retv;
	int		error;

	getcwd_retv = getcwd(buffer, CWD_BUFFER_SIZE);
	if (getcwd_retv == NULL)
		return (error_wrapper());
	error = ft_printf("%s\n", buffer);
	if (error < 0)
		return (error_wrapper());
	return (true);
}
