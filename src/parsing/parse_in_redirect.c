/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:16:32 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/12 14:32:58 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	traverse_trough_iname(t_parsing *p, char *buffer,
									size_t *buffer_i, t_inoutfiles *curr_iof)
{
	bool	success;

	success = true;
	while (p->u_input[p->inp_i] && p->u_input[p->inp_i] != ' ' && success)
	{
		if (p->u_input[p->inp_i] == '$')
		{
			curr_iof->env_var = true;
			fill_env_in_buffer(p, buffer, buffer_i);
		}
		else if (p->u_input[p->inp_i] == 39)
			success = parse_single_quote(p, buffer, buffer_i);
		else if (p->u_input[p->inp_i] == '"')
			success = parse_double_quote(p, buffer, buffer_i);
		else
			buffer[(*buffer_i)++] = p->u_input[p->inp_i++];
	}
	if (!success)
		return (false);
	return (true);
}

bool	parse_in_name(t_parsing *p, t_inoutfiles *curr_iof)
{
	char	buffer[PROC_FIELD_BUFFER];
	size_t	buffer_i;

	buffer_i = 0;
	ft_memset(buffer, '\0', PROC_FIELD_BUFFER);
	if (!(traverse_trough_iname(p, buffer, &buffer_i, curr_iof)
			|| ft_strlen(buffer) < 1))
		return (false);
	curr_iof->name = ft_strdup(buffer);
	p->task->processes[p->task->p_amount].io_amount++;
	if (!curr_iof->name)
		return (false);
	if (ft_strchr(curr_iof->name, ' ') && curr_iof->env_var)
	{
		free(curr_iof->name);
		p->task->processes[p->task->p_amount].io_amount--;
		printf("Minishell: ambiguous redirect\n");
	}
	return (true);
}

bool	parse_in_redirect(t_parsing *p)
{
	t_process		*current_process;
	t_inoutfiles	*curr_iof;

	current_process = &(p->task->processes[p->task->p_amount]);
	curr_iof = &(current_process->iofiles[current_process->io_amount]);
	curr_iof->env_var = false;
	p->inp_i++;
	if (p->u_input[p->inp_i] == '<')
	{
		p->inp_i++;
		curr_iof->type = HEREDOC;
	}
	else if (p->u_input[p->inp_i])
		curr_iof->type = IN;
	if (!p->u_input[p->inp_i])
	{
		printf("Minishell: syntax error near unexpected token 'newline'\n");
		return (false);
	}
	skip_whitespace(p);
	return (parse_in_name(p, curr_iof));
}
