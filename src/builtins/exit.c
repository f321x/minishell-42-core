/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:59:20 by marschul          #+#    #+#             */
/*   Updated: 2024/01/14 13:24:43 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_exit_var(unsigned char *exit_value, char **argv)
{
	int	i;

	*exit_value = (unsigned char) ft_atoi(argv[1]);
	i = 1;
	while (argv[1][i] != '\0')
	{
		if (ft_isdigit(argv[1][i]) == 0)
		{
			write(2, "Minishell: numeric argument required.\n", 38);
			*exit_value = 255;
			break ;
		}
		i++;
	}
}

bool	_exit_(char **argv, t_pipe *pipe_struct,
		int (*fd_array)[2], pid_t *pid_array)
{
	unsigned char	exit_value;
	extern char		**environ;

	if (argv[1] != NULL)
	{
		if (argv[1][0] == '\0' || (argv[1][0] != '-'
			&& argv[1][0] != '+' && ft_isdigit(argv[1][0]) != 1))
		{
			write(2, "Minishell: numeric argument required.\n", 38);
			exit_value = 255;
		}
		else
			set_exit_var(&exit_value, argv);
	}
	else
		exit_value = 0;
	cleanup(pipe_struct, fd_array, pid_array);
	free_vector(environ);
	rl_clear_history();
	if (isatty(0))
		ft_printf("exit\n");
	exit(exit_value);
}
