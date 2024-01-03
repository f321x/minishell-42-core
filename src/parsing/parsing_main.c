/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:03:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 13:53:44 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parsing_main(char *input, t_pipe *task)
{
	t_parsing	p;

	init_parsing_data(&p, task, input);
	while (input && input[p.inp_i])
	{

	}
}
