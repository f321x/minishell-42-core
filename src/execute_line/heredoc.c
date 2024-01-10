/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:01:08 by marschul          #+#    #+#             */
/*   Updated: 2024/01/10 13:01:48 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	write_keyword(int fd, char *keyword, int i)
{
	if (write(fd, keyword, i) == -1)
		return (false);
	else
		return (true);
}

bool	test_keyword(char *keyword, int i, char *buffer, int fd)
{
	int	is_keyword;

	is_keyword = (int) keyword[i] == buffer[0] || (buffer[0] == '\n' && \
		i == ft_strlen(keyword));
	if (! is_keyword)
	{
		if (! write_keyword(fd, keyword, i))
			return (-1);
		if (write(fd, buffer, 1) == -1)
			return (-1);
	}
	return (is_keyword);
}

int	read_line(int fd, char *keyword, int true_stdin)
{
	char	buffer[1];
	int		i;
	int		equal_to_keyword;

	i = 0;
	equal_to_keyword = true;
	buffer[0] = '\0';
	while (buffer[0] != '\n')
	{
		if (read(true_stdin, buffer, 1) == -1)
			return (-1);
		if (equal_to_keyword == 1)
			equal_to_keyword = test_keyword(keyword, i, buffer, fd);
		else
		{
			if (write(fd, buffer, 1) == -1)
				return (-1);
			if (buffer[0] == '\n')
				break ;
		}
		if (equal_to_keyword == -1)
			return (-1);
		i++;
	}
	return (equal_to_keyword);
}

int	get_here_file(char *keyword, int true_stdin, int true_stdout)
{
	int		fd;
	int		end;

	fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	end = 0;
	while (end == 0)
	{
		if (write(true_stdout, ">", 1) == -1)
			return (-1);
		end = read_line(fd, keyword, true_stdin);
	}
	close(fd);
	if (end == -1)
		return (-1);
	fd = open("tmp", O_RDONLY, 0600);
	return (fd);
}
