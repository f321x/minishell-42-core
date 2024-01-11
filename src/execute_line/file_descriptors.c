/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:12:13 by marschul          #+#    #+#             */
/*   Updated: 2024/01/11 12:31:46 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
