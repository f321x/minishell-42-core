/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:58:11 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 15:11:36 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// takes the string to print after the echo command, or after -n if existing
// if -n exists, newline is false.
bool	echo(const char *after_echo, bool n_flag)
{
	if (!n_flag)
		printf("%s\n", after_echo);
	else
		printf("%s", after_echo);
}
