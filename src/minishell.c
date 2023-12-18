/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 13:39:03 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(char **envp)
{
	t_pipe 	pipe_struct;
	char	*entered_line;
	// handlers

	while (1)
	{
		entered_line = read_a_line("minishell$ ");
		add_history(entered_line);
		pipe_struct = parse_line(entered_line);
		execute_line(pipe_struct);
	}

	return (0);
}
