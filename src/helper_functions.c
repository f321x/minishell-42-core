/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@example.invalid>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:55:26 by student          #+#    #+#             */
/*   Updated: 2024/01/08 09:05:30 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	error_wrapper(void)
{
	perror("Minishell");
	return (false);
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