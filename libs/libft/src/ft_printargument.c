/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printargument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:48:20 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:19:31 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char_argument(t_pf_data *data)
{
	while ((data->min_width > 1 && *(data->string_position) != '%')
		|| (data->min_width > 2 && *(data->string_position) == '%'))
	{
		ft_putchar_fd_pf(' ', 1, data);
		data->min_width--;
		data->letter_count++;
	}
	if (*(data->string_position) != '%')
		ft_putchar_fd_pf(va_arg(*(data->arguments), int), 1, data);
	else
		ft_putchar_fd_pf('%', 1, data);
	data->string_position++;
	data->min_width = 0;
	data->letter_count++;
}

void	ft_print_string_argument(t_pf_data *data)
{
	char	*s;
	int		strlen;

	s = va_arg(*(data->arguments), char *);
	if (!s)
		s = "(null)";
	strlen = ft_strlen(s);
	data->letter_count += strlen;
	while (data->min_width > strlen)
	{
		ft_putchar_fd_pf(' ', 1, data);
		data->letter_count++;
		data->min_width--;
	}
	data->min_width = 0;
	data->string_position++;
	ft_putstr_fd_pf(s, 1, data);
}

void	ft_print_number_argument(t_pf_data *data)
{
	char	*number_string;
	int		number_str_len;
	int		number;

	number = va_arg(*(data->arguments), int);
	number_string = ft_itoa(number);
	if (!number_string)
	{
		data->string_position++;
		data->error = 1;
		return ;
	}
	number_str_len = ft_strlen(number_string);
	data->letter_count += number_str_len;
	while (data->min_width > number_str_len || (data->put_space && number >= 0))
	{
		ft_putchar_fd_pf(' ', 1, data);
		number_str_len++;
		data->letter_count++;
		data->put_space = 0;
	}
	data->string_position++;
	data->min_width = 0;
	ft_putstr_fd_pf(number_string, 1, data);
	free(number_string);
}
