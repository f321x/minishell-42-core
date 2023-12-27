/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/27 11:18:33 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_task(t_pipe *task)
{
	task->p_amount = 0;
	task->input_file = NULL;
	task->here_file = NULL;
	task->output_file = NULL;
	task->output_file_append = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe 	task;
	char	*entered_line;

	// signal handlers

	while (1)
	{
		init_task(&task);
		task.p_amount = 0;
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;
		if (!parse_line(entered_line, &task))
			continue ;
		// for (size_t i = 0; i < task.p_amount; i++)
		// {
		// 	printf("process %zu: %s\n", i, task.processes[i].name);
		// 	while (task.processes[i].argv && *task.processes[i].argv)
		// 	{
		// 		printf("argv: %s\n", *task.processes[i].argv);
		// 		task.processes[i].argv++;
		// 	}
		// }
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
