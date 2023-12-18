/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:05:01 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:18:14 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pr_int_to_hex(t_pf_data *data, int uppercase, unsigned int number)
{
	char			buffer[12];
	int				index;

	index = 0;
	if (!number)
	{
		ft_putchar_fd_pf('0', 1, data);
		data->letter_count++;
		return ;
	}
	while (number)
	{
		buffer[index] = "0123456789abcdef"[number % 16];
		number /= 16;
		if (uppercase)
			buffer[index] = ft_toupper(buffer[index]);
		index++;
	}
	while ((data->min_width)-- > index && !data->error)
		ft_putchar_fd_pf(' ', 1, data);
	data->letter_count += index--;
	data->min_width = 0;
	while (index >= 0 && !data->error)
		ft_putchar_fd_pf(buffer[index--], 1, data);
}

void	ft_to_hex(t_pf_data *data, int uppercase)
{
	unsigned int	number;

	number = (unsigned int)va_arg(*(data->arguments), int);
	data->string_position++;
	if (!number)
	{
		while (data->min_width > 1 && !data->error)
		{
			data->min_width--;
			ft_putchar_fd_pf(' ', 1, data);
		}
	}
	pr_int_to_hex(data, uppercase, number);
}
