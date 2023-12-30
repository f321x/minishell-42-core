/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:07:12 by marschul          #+#    #+#             */
/*   Updated: 2023/12/30 21:17:10 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signum)
{
    ft_printf("\nCtrl+C was pressed. We need a new prompt.\n");
}

void sigquit_handler(int signum)
{
    ft_printf("Quit: 3\n");
	// When we are in the minishell process we dont want to print that line!
}

void	register_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}