/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:46:49 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 19:55:53 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env(void)
{
	extern char	**environ;
	int			error;

	while (environ && *environ)
	{
		error = printf("%s\n", *environ);
		if (error < 0)
		{
			perror("Printing env variable failed.")
			return (false);
		}
		environ++;
	}
	return (true);
}
