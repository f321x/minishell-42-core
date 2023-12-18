/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:45:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/30 10:56:35 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_alloc_buffer(int fd, char *fd_remainder)
{
	char	read_buffer[BUFFER_SIZE + 1];
	int		read_count;
	char	*previous_remainder;

	read_count = 1;
	while (read_count > 0 && !ft_strchr(fd_remainder, '\n'))
	{
		previous_remainder = fd_remainder;
		read_count = 0;
		while (read_count <= BUFFER_SIZE)
			read_buffer[read_count++] = '\0';
		read_count = read(fd, read_buffer, BUFFER_SIZE);
		if (read_count < 0)
		{
			if (fd_remainder)
				free(fd_remainder);
			return (NULL);
		}
		fd_remainder = ft_strjoin(fd_remainder, read_buffer);
		if (previous_remainder)
			free(previous_remainder);
		if (!fd_remainder)
			return (NULL);
	}
	return (fd_remainder);
}

static char	*cut_line(char **read_characters)
{
	char	*result_string;
	int		size;
	char	*remainder_buffer;

	size = 0;
	remainder_buffer = *read_characters;
	while ((*read_characters)[size] && (*read_characters)[size] != '\n')
		size++;
	result_string = ft_substr(*read_characters, 0, size + 1);
	if (!result_string)
	{
		free((*read_characters));
		*read_characters = NULL;
		return (NULL);
	}
	*read_characters = ft_substr(*read_characters, size + 1,
			ft_strlen(*read_characters));
	free(remainder_buffer);
	if (!(*read_characters))
	{
		free(result_string);
		return (NULL);
	}
	return (result_string);
}

char	*get_next_line(int fd)
{
	static char	*fd_remainder[1024];
	char		*result_string;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	fd_remainder[fd] = read_and_alloc_buffer(fd, fd_remainder[fd]);
	if (!fd_remainder[fd])
		return (NULL);
	result_string = cut_line(&fd_remainder[fd]);
	if (!result_string)
		return (NULL);
	if (ft_strlen(fd_remainder[fd]) == 0)
	{
		free(fd_remainder[fd]);
		fd_remainder[fd] = NULL;
	}
	if (*result_string == '\0')
	{
		free(result_string);
		return (NULL);
	}
	return (result_string);
}

// int main()
// {
// 	char *filename = "test.txt";
//     int fp = open(filename, O_RDONLY);
// 	char	*result;
// 	int		line;

// 	line = 1;
// 	if (fp == 0)
//     {
//         printf("Error: could not open file %s", filename);
//         return 1;
//     }
// 	while (line < 12)
// 	{
// 		result = get_next_line(fp);
// 		printf("%s\n", result);
// 		free(result);
// 		line++;
// 	}
// 	return (0);
// }

// if one fd read fails, free complete static or only the fd?
