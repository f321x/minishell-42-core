/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 14:54:46 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe 	parsed_command;
	char	*entered_line;

	// signal handlers

	while (1)
	{
		entered_line = read_a_line(SHELL_PROMPT);

		// testing of readline
		printf("%s\n", entered_line);
		add_history(entered_line);
		free(entered_line);
		continue ;

		if (!parse_line(entered_line, &parsed_command))
			continue ;
		// execute_line(parsed_command);
	}

	return (0);
}
