/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:06:01 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 19:06:53 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static size_t	get_size(int integer)
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

static long long	check_neg(long long integer, char **result)
{
	if (integer < 0)
	{
		**(result) = '-';
		(*result)++;
		integer *= -1;
	}
	else if (integer == 0)
	{
		**result = '0';
		(*result)++;
	}
	return (integer);
}

char	*ft_itoa(int n)
{
	char		*result;
	char		*result_start;
	int			len;
	int			power;
	long long	integer;

	integer = (long long)n;
	len = get_size(integer);
	if (integer <= 0)
		result = malloc(len * sizeof(char) + sizeof(char) * 2);
	else
		result = malloc(len * sizeof(char) + sizeof(char));
	if (!result)
		return (NULL);
	result_start = result;
	integer = check_neg(integer, &result);
	while (len)
	{
		power = pow(10, len-- - 1);
		*(result++) = '0' + (integer / power);
		integer -= power * (integer / power);
	}
	*result = '\0';
	return (result_start);
}

/* int	main()
{
	int	test = 1000034;
	char *return_array;

	return_array = ft_itoa(test);
	printf("%s", return_array);
	return (0);
} */
