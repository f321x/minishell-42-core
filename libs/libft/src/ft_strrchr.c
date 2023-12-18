/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:34:09 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/10 19:38:16 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	const char	*occurence;

	occurence = NULL;
	while (*str != '\0')
	{
		if (*str == (char)character)
			occurence = str;
		str++;
	}
	if (*str == (char)character)
		occurence = str;
	return ((char *)occurence);
}
