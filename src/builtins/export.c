/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:43:49 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 16:18:06 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// call for each pair of variable=value to export it to the env
bool	export(const char *env_var, const char *var_val)
{
	extern char **environ;

	for (int i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (true);
}
