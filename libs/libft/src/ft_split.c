/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:03:22 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/12 12:14:53 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

static size_t	gsl(char const *full_s, char c)
{
	size_t	amount;

	amount = 0;
	if (!full_s)
		return (0);
	if (*full_s != c && *full_s != '\0')
		amount++;
	while (*full_s)
	{
		if (*full_s == c && *(full_s + 1) != c && *(full_s + 1) != '\0')
			amount++;
		full_s++;
	}
	return (amount);
}

static char	*trim_string(char const *string_start_position, size_t length)
{
	char	*trimmed_string;
	size_t	index;

	index = 0;
	trimmed_string = malloc((length + 1) * sizeof(char));
	if (!trimmed_string)
		return (NULL);
	while (length > 0)
	{
		trimmed_string[index] = string_start_position[index];
		index++;
		length--;
	}
	trimmed_string[index] = '\0';
	return (trimmed_string);
}

static int	check_first_char(char ***final_array, const char *s, char c)
{
	size_t	length;

	length = 0;
	if (s[0] && s[0] != c)
	{
		while (s[length] && s[length] != c)
			length++;
		**final_array = trim_string(&(s[0]), length);
		if (!(**final_array))
			return (-1);
		(*final_array)++;
	}
	return (length);
}

static int	traverse_string(char ***f, const char *s, int i, char c)
{
	size_t	l;

	l = 0;
	if (i == -1)
		return (-1);
	while (s[i])
	{
		l = 0;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			i++;
			while (s[l + i] != c && s[l + i])
				l++;
			**f = trim_string(&(s[i]), l);
			if (!(**f))
				return (-1);
			(*f)++;
		}
		else
			i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**final_array;
	char	**start_final_array;
	int		i;
	char	**test_array;

	if (s)
		final_array = malloc((gsl(s, c) + 1) * sizeof(char *));
	if (!s || !final_array)
		return (NULL);
	start_final_array = final_array;
	test_array = final_array;
	i = check_first_char(&final_array, s, c);
	i = traverse_string(&final_array, s, i, c);
	if (i == -1)
	{
		while (*test_array)
		{
			free(*test_array);
			test_array++;
		}
		free(start_final_array);
		return (NULL);
	}
	*final_array = NULL;
	return (start_final_array);
}

/* int main()
{
	char test[] = "hello!zzzzzzzz";
	char **result = ft_split(test, 'z');

	while (*result)
	{
		printf("%s\n", *result);
		result++;
	}
	return (0);
} */
