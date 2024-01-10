/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:59:20 by marschul          #+#    #+#             */
/*   Updated: 2024/01/09 20:51:48 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_exit_(char **argv, t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	unsigned char	exit_value;
	int	i;
	extern char	**environ;

	assert(argv != NULL && ft_strcmp(argv[0], "exit") == 0); // debug

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
	free_vector(environ);
	cleanup(pipe_struct, fd_array, pid_array);
	ft_printf("exit\n");
	exit(exit_value);
}