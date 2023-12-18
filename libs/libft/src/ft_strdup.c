/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:21:17 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/06 10:33:41 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	size_t	size;
	char	*duplicate;
	char	*duplicate_start;

	size = 0;
	while (str1[size])
		size++;
	duplicate = malloc(size + 1);
	duplicate_start = duplicate;
	if (duplicate == NULL)
		return (NULL);
	while (*str1)
		*(duplicate++) = *(str1++);
	*duplicate = '\0';
	return (duplicate_start);
}
