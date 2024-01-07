/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:59:20 by marschul          #+#    #+#             */
/*   Updated: 2024/01/07 16:48:53 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_exit_(char **argv)
{
	unsigned char	exit_value;
	int	i;

	assert(argv != NULL && ft_strcmp(argv[0], "exit") == 0); // debug

	write(1, "exit\n", 5);
	if (argv[1] != NULL)
	{
		if (argv[1][0] == '\0' || (argv[1][0] != '-' && argv[1][0] != '+' && ft_isdigit(argv[1][0]) != 1))
		{
			ft_printf("Minishell: numeric argument required.\n");
			exit_value = 255;
		}
		else
		{
			exit_value = (unsigned char) ft_atoi(argv[1]);
			i = 1;
			while (argv[1][i] != '\0')
			{
				if (ft_isdigit(argv[1][i]) == 0)
				{
					ft_printf("Minishell: numeric argument required.\n");
					exit_value = 255;
					break;
				}
				i++;
			}
		}
	}
	else
		exit_value = 0;
	exit(exit_value);
}