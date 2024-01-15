/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:47 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/15 15:42:27 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_ctrld(char *entered_line)
{
	if (entered_line == NULL)
	{
		free(entered_line);
		rl_clear_history();
		free_old_env(NULL);
		exit(EXIT_SUCCESS);
	}
}

/* 
If we are running in headless mode we disable the echo.
We read with get_next_line.
If there is nothing more to read, we exit with the exit code of the last 
command.
 */
void	disable_echo_and_read(char **entered_line)
{
	struct termios		term;
	size_t				length;
	char				*exit_string;
	int					exit_value;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	*entered_line = get_next_line(0);
	length = ft_strlen(*entered_line);
	if (*entered_line && (*entered_line)[length - 1] == '\n')
		(*entered_line)[length - 1] = '\0';
	if (! *entered_line)
	{
		exit_string = getenv("?");
		exit_value = ft_atoi(exit_string);
		free(*entered_line);
		rl_clear_history();
		free_old_env(NULL);
		exit(exit_value);
	}
}

/* 
We decide if we are reading from a true terminal.
Also we fix the environment leak that occurs sometimes after readline
by saving the pointer before readline and comparing it afterwards.
 */
void	read_in(char **entered_line, char *prompt)
{
	char		**old_env;
	extern char	**environ;

	old_env = environ;
	if (! isatty(0))
		disable_echo_and_read(entered_line);
	else
		*entered_line = readline(prompt);
	if (environ != old_env)
		free(old_env);
}

// Reads a line of input from the user.
// prompt: The prompt to display to the user.
// exits if the user presses CTRL+D (EOF / 0)
// if entered line is empty it will be freed and the the loop waits for input
// returns the entered line if it is not empty
char	*read_a_line(char *prompt)
{
	char		*entered_line;

	while (1)
	{
		entered_line = NULL;
		read_in(&entered_line, prompt);
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
