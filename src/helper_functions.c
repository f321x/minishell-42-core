/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:55:26 by marschul          #+#    #+#             */
/*   Updated: 2024/01/09 20:36:36 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	error_wrapper(void)
{
	perror("Minishell");
	return (false);
}

bool	error_wrapper_bool(char *message)
{
	perror(message);
	return (false);
}

bool	error_wrapper_int(char *message)
{
	perror(message);
	return (0);
}

void	free_vector(char **vector)
{
	int	i;

	i = 0;
	while (vector[i] != NULL)
	{
		free(vector[i]);
		i++;
	}
	free(vector);
}