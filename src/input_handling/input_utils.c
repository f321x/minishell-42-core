/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:47 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/09 14:20:17 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_a_line(char *prompt)
{
	char	*entered_line;

	while (1)
	{
		entered_line = readline(prompt);  // 0 or null terminator? ctrl+d
		if (!entered_line)  // some kind of error
			continue ;
		if (!(*entered_line))  // empty line, will not be used
		{
			free(entered_line);
			continue ;
		}
		break ;
	}
	return (entered_line);
}
