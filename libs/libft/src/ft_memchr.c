/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:55:16 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/10 12:39:18 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	char	*buffer_ptr;

	buffer_ptr = (char *)ptr;
	while (num > 0)
	{
		if ((unsigned char)*buffer_ptr == (unsigned char)value)
			return ((void *)buffer_ptr);
		num--;
		buffer_ptr++;
	}
	return (NULL);
}
