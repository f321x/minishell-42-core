/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:46:49 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 13:36:54 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env(char **argv)
{
	extern char	**environ;
	char		**pointer;
	int			error;

	if (argv[1] != NULL)
		return (error_wrapper());
	pointer = environ;
	while (pointer && *pointer)
	{
		error = ft_printf("%s\n", *pointer);
		if (error < 0)
			return (error_wrapper());
		pointer++;
	}
	return (true);
}
