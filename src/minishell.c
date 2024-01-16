/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/16 12:03:27 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_exit_code(void)
{
	char	*argv[4];

	argv[0] = "export";
	argv[1] = "?=0";
	argv[2] = NULL;
	export(argv);
}

int	main(void)
{
	t_pipe	task;
	char	*entered_line;

	register_signal_handlers();
	initialize_exit_code();
	while (1)
	{
		task.p_amount = 0;
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;
		if (!parsing_main(entered_line, &task))
		{
			free(entered_line);
			continue ;
		}
		free(entered_line);
		execute_line(&task);
	}
	return (0);
}
