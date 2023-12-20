/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:46:49 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 15:55:07 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Should we give out error, when there is an argument to the command, or not?
bool	env(char **argv)
{
	extern char	**environ;
	char		**pointer;
	int			error;

	pointer = environ;
	while (pointer && *pointer)
	{
		error = ft_printf("%s\n", *pointer);
		if (error < 0)
		{
			perror("Printing env variable failed.");
			return (false);
		}
		pointer++;
	}
	return (true);
}
