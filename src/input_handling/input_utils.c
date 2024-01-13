/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:47 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/13 13:57:46 by marschul         ###   ########.fr       */
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

void	disable_echo_and_read(char **entered_line)
{
	struct termios		term;
	size_t				length;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	*entered_line = get_next_line(0);
	length = ft_strlen(*entered_line);
	if (*entered_line && (*entered_line)[length - 1] == '\n')
		(*entered_line)[length - 1] = '\0';
	if (! *entered_line)
		exit(0);
}

// Reads a line of input from the user.
// prompt: The prompt to display to the user.
// exits if the user presses CTRL+D (EOF / 0)
// if entered line is empty it will be freed and the the loop waits for input
// returns the entered line if it is not empty
char	*read_a_line(char *prompt)
{
	char			*entered_line;

	while (1)
	{
		// if (! isatty(0))
		// 	disable_echo_and_read(&entered_line);
		// else
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
