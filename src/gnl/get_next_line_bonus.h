/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:46:34 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:10:43 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_substr(char *s, int start, size_t len);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strlen(const char *string);
char	*ft_strchr(const char *str, int character);

#endif
