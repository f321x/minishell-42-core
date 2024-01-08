/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/08 10:47:27 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_task(t_pipe *task)
{
	task->p_amount = 0;
	// task->input_file = NULL;
	// task->here_file = NULL;
	// task->output_file = NULL;
	// task->output_file_append = NULL;
}

void	initialize_exit_code(void)
{
	char	*argv[3];

	argv[0] = "export";
	argv[1] = "?=0";
	argv[2] = NULL;
	export(argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe 	task;
	char	*entered_line;

	// register signal handlers
	register_signal_handlers();

	// initialize env var ? mit 0
	initialize_exit_code();

	while (1)
	{
		init_task(&task);
		task.p_amount = 0;
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;
		if (!parsing_main(entered_line, &task))
		{
			printf("parsing dead\n");
			continue ;
		}
		for (size_t i = 0; i < task.p_amount; i++)
		{
			int in = 0;
			printf("argv:");
			while (task.processes[i].argv && task.processes[i].argv[in])
			{
				printf(" %s", task.processes[i].argv[in]);
				// task.processes[i].argv;
				in++;
			}
			printf("\n");
		}
		printf("\n");
		// continue;
		execute_line(&task)

		// free(entered_line);
		printf("\n");
		continue ;

		// if (!parse_line(entered_line, &task))
		// 	continue ;
		// execute_line(parsed_command);
	}
	free_old_env(NULL);
	return (0);
}
