/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@example.invalid>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:59:20 by student          #+#    #+#             */
/*   Updated: 2023/12/29 18:04:22 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_exit_(char **argv)
{
	int	return_value;

	if (argv != NULL && argv[1] != NULL)
		return_value = ft_atoi(argv[1]);
	else
		return_value = 0;
	exit(return_value);
}