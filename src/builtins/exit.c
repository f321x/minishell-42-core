/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:59:20 by marschul          #+#    #+#             */
/*   Updated: 2024/01/01 18:45:40 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_exit_(char **argv)
{
	int	exit_value;
	int	i;

	assert(argv != NULL && ft_strcmp(argv[0], "exit") == 0); // debug

	if (argv[1] != NULL)
	{
		exit_value = (char) ft_atoi(argv[1]);
		i = 0;
		while (argv[1][i] != '\0')
		{
			if (ft_isdigit(argv[1][i]) == 0)
			{
				ft_printf("Minishell: Numeric argument required.\n");
				exit_value = 255;
				break;
			}
			i++;
		}
	}
	else
		exit_value = 0;
	exit(exit_value);
}