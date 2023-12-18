/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:55:13 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 17:07:19 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	size_t			index;
	unsigned char	*buffer_dest;
	unsigned char	*buffer_src;

	index = 0;
	if (!destination && !source)
		return (NULL);
	buffer_dest = (unsigned char *)destination;
	buffer_src = (unsigned char *)source;
	while (num)
	{
		if (source < destination && destination < source + num)
			buffer_dest[num - 1] = buffer_src[num - 1];
		else
		{
			buffer_dest[index] = buffer_src[index];
			index++;
		}
		num--;
	}
	return (destination);
}
