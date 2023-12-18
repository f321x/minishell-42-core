/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:33:27 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 14:14:23 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	char	*substring_start;
	size_t	remaining_len;

	if (ft_strlen(s) < start)
		start = ft_strlen(s);
	remaining_len = ft_strlen(s) - start;
	if (remaining_len < len)
		substring = malloc(remaining_len + 1);
	else
		substring = malloc(len + 1);
	if (substring == NULL || s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		*substring = '\0';
		return (substring);
	}
	substring_start = substring;
	while (len-- > 0 && s[start])
		*(substring++) = s[start++];
	*substring = '\0';
	return (substring_start);
}
