/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_iofiles1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:09 by marschul          #+#    #+#             */
/*   Updated: 2024/01/15 15:36:05 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_infile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_RDONLY | O_NONBLOCK, 0600);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_infile"));
	if (dup2(fd, 0) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_infile"));
	return (true);
}

/* 
We only need one tmp file surprisingly, and it will be opened in /tmp/username
 */
bool	handle_herefile(t_inoutfiles *file, int true_stdin, int true_stdout)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = get_here_file(name, true_stdin, true_stdout);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_herefile"));
	if (dup2(fd, 0) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_herefile"));
	return (true);
}

bool	handle_outfile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_outfile"));
	if (dup2(fd, 1) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_outfile"));
	return (true);
}

bool	handle_appendfile(t_inoutfiles *file)
{
	int		fd;
	char	*name;

	name = file->name;
	fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd == -1)
		return (error_wrapper_bool("Minishell: handle_appendfile"));
	if (dup2(fd, 1) == -1 || close(fd) == -1)
		return (error_wrapper_bool("Minishell: handle_appendfile"));
	return (true);
}

/* 
loops over every indirection and opens files.
 */
bool	handle_inoutfiles(t_process *process, int true_inout_fds[2])
{
	int				i;
	int				return_value;
	t_inoutfiles	*file;
	int				true_stdin;
	int				true_stdout;

	true_stdin = true_inout_fds[0];
	true_stdout = true_inout_fds[1];
	i = 0;
	while (i < process->io_amount)
	{
		file = &process->iofiles[i];
		if (file->type == IN)
			return_value = handle_infile(file);
		if (file->type == OUT)
			return_value = handle_outfile(file);
		if (file->type == HEREDOC)
			return_value = handle_herefile(file, true_stdin, true_stdout);
		if (file->type == APPEND)
			return_value = handle_appendfile(file);
		if (return_value == false)
			return (false);
		i++;
	}
	return (true);
}
