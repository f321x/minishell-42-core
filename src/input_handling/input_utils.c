/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:47 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/11 17:37:44 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_ctrld(char *entered_line)
{
	if (entered_line == 0)
	{
		free(entered_line);
		free_old_env(NULL);
		exit(EXIT_SUCCESS);
	}
}

// Reads a line of input from the user.
// prompt: The prompt to display to the user.
// exits if the user presses CTRL+D (EOF / 0)
// if entered line is empty it will be freed and the the loop waits for input
// returns the entered line if it is not empty
char	*read_a_line(char *prompt)
{
	char	*entered_line;

	while (1)
	{
		entered_line = readline(prompt);
		check_if_ctrld(entered_line);
		if (!entered_line)
			continue ;
		if (!(*entered_line))
		{
			free(entered_line);
			continue ;
		}
		if (ft_strlen(entered_line) > CWD_BUFFER_SIZE)
		{
			free(entered_line);
			printf("Command too long!\n");
			continue ;
		}
		break ;
	}
	return (entered_line);
}
