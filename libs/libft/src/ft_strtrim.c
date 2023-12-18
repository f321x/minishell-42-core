/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 19:20:27 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>

/* static char	*ft_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == (char)character)
			return ((char *)str);
		str++;
	}
	if (*str == (char)character)
		return ((char *)str);
	return (NULL);
}

static size_t	ft_strlen(const char *string)
{
	size_t	counter;

	counter = 0;
	while (string[counter] != '\0')
		counter++;
	return (counter);
} */

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*returned_string;
	char		*returned_string_start;
	size_t		start;
	size_t		end;

	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start] != '\0')
		start++;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	if (s1[start])
		returned_string = malloc((end - start) + 2);
	else
		returned_string = malloc(1);
	if (!returned_string)
		return (NULL);
	returned_string_start = returned_string;
	while (start <= end && s1[start])
		*(returned_string++) = s1[start++];
	*returned_string = '\0';
	return (returned_string_start);
}
/* int main()
{
	ft_strtrim("", "");
	ft_strtrim("", "cdef");
	return (1);
} */
