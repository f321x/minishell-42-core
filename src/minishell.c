/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 14:25:42 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe 	task;
	char	*entered_line;

	// signal handlers

	while (1)
	{
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;

		free(entered_line);
		continue ;

		// if (!parse_line(entered_line, &task))
		// 	continue ;
		// execute_line(parsed_command);
	}

	free_old_env(NULL);
	return (0);
}
