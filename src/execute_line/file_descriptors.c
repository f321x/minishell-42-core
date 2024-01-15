/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:12:13 by marschul          #+#    #+#             */
/*   Updated: 2024/01/15 15:26:48 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
We close all file descriptors in fd_array in the child process.
Some have already been closed, that's why I don't handle errors on close.
It was easier so, it's not really correct programming...
 */
void	close_all_fds(int (*fd_array)[2], size_t p_amount)
{
	size_t	i;

	i = 0;
	while (i < p_amount - 1)
	{
		close(fd_array[i][0]);
		close(fd_array[i][1]);
		i++;
	}
}

/* 
The parent process always closes the last pair of file descriptors, so that
the last pipe is always closed. That is important, since programs that expect
EOF won't terminate otherwise.
 */
bool	close_last_fds(int (*fd_array)[2], size_t i)
{
	if (i == 0)
		return (1);
	else
	{
		if (close(fd_array[i - 1][0]) == -1)
			return (error_wrapper_bool("Minishell: close_last_fds"));
		if (close(fd_array[i - 1][1]) == -1)
			return (error_wrapper_bool("Minishell: close_last_fds"));
	}
	return (true);
}

/* 
Sometimes we have to restore our true stdin and stdout.
 */
void	restore_fds(int (*fd_array)[2], size_t p_amount)
{
	close_all_fds(fd_array, p_amount);
	if (dup2(fd_array[p_amount - 1][0], 0) == -1 || \
		dup2(fd_array[p_amount - 1][1], 1) == -1)
		perror("Minishell: restore_fds");
	if (close(fd_array[p_amount - 1][0]) == -1 || \
		close(fd_array[p_amount - 1][1]) == -1)
		perror("Minishell: restore_fds");
}
