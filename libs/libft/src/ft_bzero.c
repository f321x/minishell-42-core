/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:44:22 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/11 13:33:32 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	char	*buffer_pointer;

	buffer_pointer = (char *)s;
	while (n > 0)
	{
		*buffer_pointer = '\0';
		buffer_pointer++;
		n--;
	}
}
/* int main()
{
	char	str[] = "this is just a test";
	size_t	num = 5;
	int		counter = 0;

	ft_bzero(str, num);
	while (str[counter] == '\0')
		counter++;
	if (counter == num)
		printf("success");
	return (1);
} */
