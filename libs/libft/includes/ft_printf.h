/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:49:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/12 10:13:38 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct printf_data
{
	va_list			*arguments;
	size_t			letter_count;
	const char		*string_position;
	int				min_width;
	int				error;
	int				put_space;
	int				pad_zero;
}	t_pf_data;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t num, size_t size);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
void	ft_putchar_fd_pf(char c, int fd, t_pf_data *data);
void	ft_putstr_fd_pf(char *s, int fd, t_pf_data *data);
size_t	ft_strlen(const char *string);
int		ft_toupper(int c);
void	ft_ox(t_pf_data *data);
void	ft_space(t_pf_data *data);
void	ft_sign(t_pf_data *data);
void	ft_to_hex(t_pf_data *data, int uppercase);
void	ft_print_char_argument(t_pf_data *data);
void	ft_print_string_argument(t_pf_data *data);
void	ft_print_number_argument(t_pf_data *data);
int		ft_printf(const char *first_arg, ...);
void	ft_print_ptr(t_pf_data *data);
void	ft_putunsigned(t_pf_data *data);
void	ft_check_char(t_pf_data *data);
void	ft_parse_arg(t_pf_data *data);
void	ft_check_bonus(t_pf_data *data);
char	*ft_get_digit(const char *string_pos);

#endif
