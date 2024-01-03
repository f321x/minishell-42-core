/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@example.invalid>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:07:12 by student          #+#    #+#             */
/*   Updated: 2023/12/30 23:29:41 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signum)
{
    ft_printf("\nCtrl+C was pressed. We need a new prompt.\n");
}

void	register_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
