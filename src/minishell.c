/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 18:07:47 by ***REMOVED***            ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_pipe 	task;
	char	*entered_line;

	// register signal handlers
	register_signal_handlers();

	while (1)
	{
		init_task(&task);
		task.p_amount = 0;
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;
		if (!parsing_main(entered_line, &task))
			continue ;

		// for (size_t i = 0; i < task.p_amount; i++)
		// {
		// 	printf("argv:");
		// 	while (task.processes[i].argv && *task.processes[i].argv)
		// 	{
		// 		printf(" %s", *task.processes[i].argv);
		// 		task.processes[i].argv++;
		// 	}
		// 	printf("\n");
		// }
		// continue;

		execute_line(&task);
		// free(entered_line);
		continue ;

		// if (!parse_line(entered_line, &task))
		// 	continue ;
		// execute_line(parsed_command);
	}
	free_old_env(NULL);
	return (0);
}
