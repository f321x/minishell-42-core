/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:08:09 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 17:23:41 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static size_t	ft_strlen(const char *string)
{
	size_t	counter;

	counter = 0;
	while (string[counter] != '\0')
		counter++;
	return (counter);
} */

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*dest_start;
	size_t	len_dest_init;
	size_t	len_dest;
	size_t	len_src;

	dest_start = dest;
	len_src = 0;
	len_dest = 0;
	if (!src)
		src++;
	len_src = ft_strlen(src);
	if (dest)
		len_dest = ft_strlen(dest);
	len_dest_init = len_dest;
	if (len_dest_init >= size)
		return (size + len_src);
	while (*dest)
		dest++;
	while ((size - len_dest++) > 1 && *src)
		*(dest++) = *(src++);
	*dest = '\0';
	return (len_dest_init + len_src);
}

/* int main()
{
	char b[0xF] = "nyan !";
    ft_strlcat(b, ((void *)0), 2);
	return (1);
} */
