/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:03:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 11:47:09 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parsing_main(char *input, t_pipe *task)
{
	t_parsing	p;

	init_parsing_data(&p, task, input);
	while (input && input[p.line_i])
	{

	}
}
