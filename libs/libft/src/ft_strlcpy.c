/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:53:58 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/10 14:27:59 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t size)
{
	size_t	index;
	size_t	src_length;

	index = 0;
	src_length = ft_strlen(source);
	if (size == 0 || !destination || !source)
		return (src_length);
	while (source[index] != '\0' && index < size - 1)
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (src_length);
}
