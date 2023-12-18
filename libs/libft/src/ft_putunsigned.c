/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:09:54 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:20:09 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size(long long integer)
{
	size_t	size;

	size = 0;
	if (integer == 0)
		return (1);
	while (integer)
	{
		integer /= 10;
		size++;
	}
	return (size);
}

static int	pow(int base_number, int exponent)
{
	int	index;

	index = base_number;
	if (exponent == 0)
		return (1);
	while (exponent > 1)
	{
		base_number = base_number * index;
		exponent--;
	}
	return (base_number);
}

void	ft_min_width(t_pf_data *data, int number_size, long long number)
{
	if (number < 0)
		data->min_width--;
	while (data->min_width > number_size)
	{
		ft_putchar_fd_pf(' ', 1, data);
		data->letter_count++;
		number_size++;
	}
	data->min_width = 0;
}

static int	check_zero(long long *number, int len, t_pf_data *data)
{
	int	error;

	if (*number < 0)
	{
		error = write(1, "-", 1);
		if (error == -1)
		{
			data->error = 1;
			return (0);
		}
		*number *= -1;
		data->letter_count++;
	}
	if (*number == 0)
	{
		error = write(1, "0", 1);
		if (error == -1)
			data->error = 1;
		return (0);
	}
	return (len);
}

void	ft_putunsigned(t_pf_data *data)
{
	size_t		len;
	int			power;
	char		buffer;
	long long	number;
	int			error;

	number = (long long)va_arg(*(data->arguments), unsigned int);
	data->string_position++;
	len = get_size(number);
	ft_min_width(data, len, number);
	data->letter_count += len;
	len = check_zero(&number, len, data);
	while (len && !data->error)
	{
		power = pow(10, len-- - 1);
		buffer = '0' + (number / power);
		error = write(1, &buffer, 1);
		if (error == -1)
			data->error = 1;
		number -= power * (number / power);
	}
}
