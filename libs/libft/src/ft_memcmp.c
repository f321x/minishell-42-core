/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:02:46 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/10 20:04:45 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	unsigned char	*buffer1;
	unsigned char	*buffer2;

	buffer1 = (unsigned char *)ptr1;
	buffer2 = (unsigned char *)ptr2;
	while (num > 0 && *buffer1 == *buffer2)
	{
		num--;
		buffer1++;
		buffer2++;
	}
	if (num == 0)
		return (0);
	return (*buffer1 - *buffer2);
}
