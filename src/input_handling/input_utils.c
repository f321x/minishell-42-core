/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@example.invalid>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:47 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/09 13:47:01 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_a_line(char *prompt)
{
	char	*entered_line;

	while (1)
	{
		entered_line = readline(prompt);
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
