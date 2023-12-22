/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:57:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/22 14:40:11 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*return_string;
	char	*return_string_start;

	return_string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (return_string == NULL)
		return (NULL);
	return_string_start = return_string;
	while (s1 && *s1)
		*(return_string++) = *(s1++);
	while (s2 && *s2)
		*(return_string++) = *(s2++);
	*return_string = '\0';
	return (return_string_start);
}
