/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:45:50 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/10 20:00:57 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	while (num > 0 && *str1 == *str2 && *str1 != '\0' && *str2 != '\0')
	{
		str1++;
		str2++;
		num--;
	}
	if (num == 0)
		return (0);
	return ((unsigned char)*str1 - (unsigned char)*str2);
}
