/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:21:57 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 13:01:01 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *l, size_t len)
{
	const char	*big_position;
	const char	*little_start;
	size_t		len_remaining;

	little_start = l;
	if (*l == '\0')
		return ((char *)big);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (len > 0)
	{
		big_position = big;
		len_remaining = len;
		while (*big == *l && len > 0 && *big != '\0' && *(l++) != '\0')
		{
			big++;
			len--;
		}
		if (*l == '\0')
			return ((char *)big_position);
		big = big_position + 1;
		len = len_remaining - 1;
		l = little_start;
	}
	return (NULL);
}
