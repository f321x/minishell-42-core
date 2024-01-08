/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:44:42 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/08 14:31:51 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_in_redirect(t_parsing *p)
{
	t_process		*current_process;
	t_inoutfiles	*curr_iof;

	return (false); // tbd
	// current_process = &(p->task->processes[p->task->p_amount]);
	// curr_iof = &(current_process->iofiles[current_process->io_amount]);
	// p->inp_i++;
	// if (p->u_input[p->inp_i] == '<')
	// {
	// 	p->inp_i++;
	// 	curr_iof->type = HEREDOC;
	// }
	// else if (p->u_input[p->inp_i])
	// 	curr_iof->type = IN;
	// skip_whitespace(p);
	// if (!ft_isdelimiter(p->u_input[p->inp_i]))
	// 	return (parse_in_name(p, curr_iof));
	// return (false);
}

static bool	parse_out_name(t_parsing *p, t_inoutfiles *curr_iof)
{
	char	buffer[PROC_FIELD_BUFFER];
	size_t	buffer_i;

	buffer_i = 0;
	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ')
	{
		if (p->u_input[p->inp_i] == '$')
			fill_env_in_buffer(p, buffer, PROC_FIELD_BUFFER);
		else if (p->u_input[p->inp_i] == 39)
		{
			p->inp_i++;
			while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != 39)
				buffer[buffer_i++] = p->u_input[p->inp_i++];
			if (p->u_input[p->inp_i] != 39)
				return (false);
		}
		else if (p->u_input[p->inp_i] == '"')
		{
			p->inp_i++;
			while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != '"')
			{
				if (p->u_input[p->inp_i] == '$')
					fill_env_in_buffer(p, buffer, PROC_FIELD_BUFFER);
				else
					buffer[buffer_i++] = p->u_input[p->inp_i++];
			}
			if (p->u_input[p->inp_i] != '"')
				return (false);
		}
		else
			buffer[buffer_i++] = p->u_input[p->inp_i++];
	}
	if (ft_strlen(buffer) < 1)
		return (false);  // ???
	curr_iof->name = ft_strdup(buffer);
	printf("BUFFER: %s\n", curr_iof->name);
	p->task->processes[p->task->p_amount].io_amount++;
	if (!curr_iof->name)
		return (false);
	return (true);

	// works but without quotes or env variables
	// size_t	name_l;
	// size_t	buff_i;
	// size_t	name_i;

	// buff_i = p->inp_i;
	// name_i = 0;
	// while (p->u_input[buff_i] && !ft_isdelimiter(p->u_input[buff_i]))
	// 	buff_i++;
	// if (buff_i > p->inp_i)
	// 	curr_iof->name = ft_calloc((buff_i - p->inp_i) + 1, sizeof(char));
	// else
	// 	return (false);
	// if (!curr_iof->name)
	// 	return (false);
	// while (buff_i > p->inp_i)
	// 	curr_iof->name[name_i++] = p->u_input[p->inp_i++];
	// p->task->processes[p->task->p_amount].io_amount++;
	// return (true);
}

bool	parse_out_redirect(t_parsing *p)
{
	t_process		*current_process;
	t_inoutfiles	*curr_iof;

	current_process = &(p->task->processes[p->task->p_amount]);
	curr_iof = &(current_process->iofiles[current_process->io_amount]);
	p->inp_i++;
	if (p->u_input[p->inp_i] == '>')
	{
		p->inp_i++;
		curr_iof->type = APPEND;
	}
	else if (p->u_input[p->inp_i])
		curr_iof->type = OUT;
	skip_whitespace(p);
	// if (!ft_isdelimiter(p->u_input[p->inp_i]))
	// 	return (parse_out_name(p, curr_iof));
	return (parse_out_name(p, curr_iof));
}
