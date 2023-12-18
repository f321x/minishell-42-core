/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:17:05 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:20:36 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ox(t_pf_data *data)
{
	va_list	arg;

	va_copy(arg, *(data->arguments));
	data->string_position++;
	if (va_arg(arg, int) == 0)
		;
	else if (*(data->string_position) == 'x')
	{
		ft_putstr_fd_pf("0x", 1, data);
		data->letter_count += 2;
	}
	else if (*(data->string_position) == 'X')
	{
		ft_putstr_fd_pf("0X", 1, data);
		data->letter_count += 2;
	}
	va_end(arg);
	ft_parse_arg(data);
}

void	ft_space(t_pf_data *data)
{
	data->put_space = 1;
	data->string_position++;
	ft_parse_arg(data);
}

void	ft_sign(t_pf_data *data)
{
	va_list	arg;

	va_copy(arg, *(data->arguments));
	if (va_arg(arg, int) >= 0)
	{
		ft_putchar_fd_pf('+', 1, data);
		data->letter_count++;
	}
	data->string_position++;
	va_end(arg);
	ft_parse_arg(data);
}
