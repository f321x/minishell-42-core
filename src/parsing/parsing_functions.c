/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:40:15 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/10 12:53:47 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// traverses trough the given userinput till it reaches a
// delimiter character and stores the chars in a buffer variable,
// then the buffer will be appended as new argv string to the current (new)
// process (pipe struct) if it is longer than 0
bool	parse_name(t_parsing *p)
{
	char		buffer[PROC_FIELD_BUFFER];
	size_t		index;
	t_process	*curr_proc;

	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	index = 0;
	curr_proc = &(p->task->processes[p->task->p_amount]);
	while (!ft_isdelimiter(p->u_input[p->inp_i]))
	{
		buffer[index] = p->u_input[p->inp_i];
		p->inp_i++;
		index++;
	}
	if (index > 0)
	{
		curr_proc->argv = append_string(curr_proc->argv, buffer);
		if (!curr_proc->argv)
			return (false);
	}
	p->new_proc = false;
	return (true);
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
	else if (current_c == '"')
		return (parse_double_quote(p));
	else if (current_c == 39)
		return (parse_single_quote(p));
	else
		return (add_to_argv(p));
	return (true);
}
