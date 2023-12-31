/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:47 by fbock             #+#    #+#             */
/*   Updated: 2024/01/09 16:01:54 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads a line of input from the user.
// prompt: The prompt to display to the user.
// exits if the user presses CTRL+D (EOF / 0)
// if entered line is empty it will be freed and the the loop waits for input
// returns the entered line if it is not empty
char *read_a_line(char *prompt)
{
	char	*entered_line;

	while (1)
	{
		entered_line = readline(prompt);  // 0 or null terminator? ctrl+d
		if (entered_line == 0)
		{
			free(entered_line);
			exit(EXIT_SUCCESS);
		}
		if (!entered_line)  // some kind of error
			continue ;
		if (!(*entered_line))  // empty line, will not be used
		{
			free(entered_line);
			continue ;
		}
		break ;
	}
	return (entered_line);
}
