/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:03:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/04 16:20:23 by ***REMOVED***            ###   ########.fr       */
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
		if (p.new_proc && input[p.inp_i] &&
			!ft_isdelimiter(input[p.inp_i]))
		{
			if (!parse_name(&p))
				return (free_all_argvs(&p));
			skip_whitespace(&p);
		}
		if (!parse_delimiter(&p))
			return (free_all_argvs(&p));
		if (p.new_proc)
			p.task->p_amount++;
	}
	p.task->p_amount++;
	return (true);
}
