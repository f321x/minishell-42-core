/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:48:03 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 17:06:35 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	unsigned char	*buffer_src;
	unsigned char	*buffer_dest;

	buffer_src = (unsigned char *)source;
	buffer_dest = (unsigned char *)destination;
	if (!destination && !source)
		return (NULL);
	while (num > 0)
	{
		*buffer_dest = *buffer_src;
		buffer_dest++;
		buffer_src++;
		num--;
	}
	return (destination);
}

/* int main()
{
	ft_memcpy(((void *)0), ((void *)0), 3);
	return (1);
} */
