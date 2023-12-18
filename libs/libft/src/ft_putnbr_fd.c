/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:55:29 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:12:18 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(long long integer)
{
	size_t	size;

	size = 0;
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

void	ft_putnbr_fd(int n, int fd)
{
	size_t		len;
	int			power;
	char		buffer;
	long long	number;

	number = (long long)n;
	len = get_size(number);
	if (number < 0)
	{
		write(fd, "-", 1);
		number *= -1;
	}
	else if (number == 0)
		write(fd, "0", 1);
	while (len)
	{
		power = pow(10, len-- - 1);
		buffer = '0' + (number / power);
		write(fd, &buffer, 1);
		number -= power * (number / power);
	}
}

/* int main()
{
	ft_putnbr_fd(1000, 1);
	return (1);
} */
