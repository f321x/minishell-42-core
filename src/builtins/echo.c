/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:58:11 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/19 20:46:56 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// takes the string to print after the echo command, or after -n if existing
// if -n exists, newline is false. ENV variables have to be placed in the
// string beforehand.
bool	echo(char **argv)
{
	int		error;
	int 	i;
	bool	n_flag;

	if (argv[1] != NULL && ft_strncmp("-n", argv[1], 3) == 0)
	{
		n_flag = true;
		i = 2;
	}
	else
		i = 1;
	while (argv[i] != NULL)
	{

		// error = printf("+%s+", argv[i]);
		error = write(1, argv[i], ft_strlen(argv[i]));
		if (error < 0)
		{
			perror("Error printing echo.");
			return (false);
		}
		i++;
	}
	if (!n_flag)
		error = printf("\n");
	if (error < 0)
	{
		perror("Error printing echo.");
		return (false);
	}
	return (true);
}
