/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:58:11 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/11 20:53:20 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_check(bool *n_flag, int *error)
{
	if (!(*n_flag))
		*error = ft_printf("\n");
	if (*error < 0)
		return (error_wrapper());
	return (true);
}

// takes the string to print after the echo command, or after -n if existing
// if -n exists, newline is false. ENV variables have to be placed in the
// string beforehand.
bool	echo(char **argv)
{
	int		error;
	int		i;
	bool	n_flag;

	n_flag = false;
	if (argv[1] != NULL && ft_strncmp("-n", argv[1], 3) == 0)
	{
		n_flag = true;
		i = 2;
	}
	else
		i = 1;
	while (argv[i] != NULL)
	{
		error = ft_printf("%s", argv[i]);
		if (error < 0)
			return (error_wrapper());
		if (argv[i + 1] != NULL)
			error = ft_printf(" ");
		if (error < 0)
			return (error_wrapper());
		i++;
	}
	return (error_check(&n_flag, &error));
}
