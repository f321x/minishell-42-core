/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:58:11 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 19:09:44 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// takes the string to print after the echo command, or after -n if existing
// if -n exists, newline is false. ENV variables have to be placed in the
// string beforehand.
bool	echo(const char *after_echo, bool n_flag)
{
	int	error;

	if (!n_flag)
		error = printf("%s\n", after_echo);
	else
		error = printf("%s", after_echo);
	if (error < 0)
	{
		perror("Error printing echo.");
		return (false);
	}
	return (true);
}
