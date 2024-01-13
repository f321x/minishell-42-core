/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:07:01 by marschul          #+#    #+#             */
/*   Updated: 2024/01/13 18:09:05 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_processes(t_pipe *pipe_struct)
{
	size_t	i;
	long	j;

	i = 0;
	while (i < pipe_struct->p_amount)
	{
		free_vector(pipe_struct->processes[i].argv);
		j = 0;
		while (j < pipe_struct->processes[i].io_amount)
		{
			free(pipe_struct->processes[i].iofiles[j].name);
			j++;
		}
		i++;
	}
}

int	cleanup(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array)
{
	char	tmp_name[PATH_MAX];

	restore_fds(fd_array, pipe_struct->p_amount);
	free(pid_array);
	free(fd_array);
	free_processes(pipe_struct);
	if (! get_tmp_name(tmp_name))
		return (0);
	if (access(tmp_name, F_OK) == 0)
		if (unlink(tmp_name) == -1)
			perror("Minishell: cleanup");
	return (0);
}

bool	create_pid_array(pid_t **pid_array, size_t p_amount)
{
	*pid_array = malloc(p_amount * sizeof(p_amount));
	if (*pid_array == NULL)
		return (error_wrapper_bool("Minishell: create_pid_array"));
	else
		return (true);
}

bool	create_fd_array(int (*(*fd_array))[2], size_t n)
{
	int	(*res)[2];

	res = (int (*)[2])malloc(sizeof(int [n][2]));
	*fd_array = res;
	if (*fd_array == NULL)
		return (error_wrapper_bool("Minishell: create_fd_array"));
	(*fd_array)[n - 1][0] = dup(0);
	(*fd_array)[n - 1][1] = dup(1);
	return (true);
}

bool	create_pipes(int (*fd_array)[2], size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pipe(fd_array[i]) == -1)
			return (error_wrapper_bool("Minishell: create_pipes"));
		i++;
	}
	return (true);
}
