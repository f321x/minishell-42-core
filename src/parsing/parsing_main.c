/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/19 10:11:31 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	check_builtin(t_parsing *input)
// {
// 	if (ft_strcmp(*(input->tokens), "cd") == 0)
// 		cd(*(++input->tokens));
// 	else if (ft_strcmp(string, "echo") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "env") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "export") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "pwd") == 0)
// 	{

// 	}
// 	else if (ft_strcmp(string, "unset") == 0)
// 	{

// 	}
// 	return (false);
// }

bool	parse_line(char *entered_line, t_pipe parsed_command)
{
	// pipe_struct	parsed_args;
	// t_parsing	input;
	char		**tokens;

	tokens = ft_split(entered_line, ' ');
	if (!tokens)
		return (false);

	while (*tokens)  // check if token is builtin before creating processes...
	{
		check_builtin(&input);

		input.tokens++;
	}
	return (true);
}
