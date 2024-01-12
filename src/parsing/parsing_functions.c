/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:40:15 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/12 14:39:04 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// traverses trough the given userinput till it reaches a
// delimiter character and stores the chars in a buffer variable,
// then the buffer will be appended as new argv string to the current (new)
// process (pipe struct) if it is longer than 0
bool	parse_name(t_parsing *p)
{
	bool	result;

	result = parse_remaining(p);
	p->new_proc = false;
	return (result);
}

// checks the character for certain delimiter characters
// if a delimiter is matched it will call the correct function
// to parse the type (for example env variables with $)
// else add_to_argv is called.
// in case the first char is a delimiter (new_proc true),
// it will set new_proc false.
bool	parse_delimiter(t_parsing *p)
{
	char	current_c;

	current_c = p->u_input[p->inp_i];
	if (!current_c)
		return (true);
	if (p->new_proc)
		p->new_proc = false;
	else if (current_c == '>')
		return (parse_out_redirect(p));
	else if (current_c == '<')
		return (parse_in_redirect(p));
	else if (current_c == '|')
		return (handle_pipe(p));
	else if (current_c == '$')
		return (parse_env_var(p));
	else
		return (parse_remaining(p));
	return (true);
}
