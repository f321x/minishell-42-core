/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:03:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/03 14:56:03 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parsing_main(char *input, t_pipe *task)
{
	t_parsing	p;

	init_parsing_data(&p, task, input);
	while (input && input[p.inp_i])
	{
		skip_whitespace(&p);
		if (p.new_proc)  // will be true at the beginning and after pipe |
		{
			if (!parse_name(&p))
				return (false);
			skip_whitespace(&p);
		}
		if (!parse_delimiter(&p))
			return (false);
	}
	return (true);
}
