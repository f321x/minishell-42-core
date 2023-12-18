/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:57:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/06 13:30:22 by ***REMOVED***            ###   ########.fr       */
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
	while (*s1)
		*(return_string++) = *(s1++);
	while (*s2)
		*(return_string++) = *(s2++);
	*return_string = '\0';
	return (return_string_start);
}
