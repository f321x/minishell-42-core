/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:46:49 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/01 18:02:48 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env(char **argv)
{
	extern char	**environ;
	char		**pointer;
	int			error;

	assert(argv != NULL && ft_strcmp(argv[0], "env") == 0); // debug

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
