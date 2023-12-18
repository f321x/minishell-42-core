/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:54:32 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/19 12:42:37 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *first_arg, ...)
{
	va_list			args;
	t_pf_data		*data;
	int				letter_count;

	va_start(args, first_arg);
	data = malloc(sizeof(t_pf_data));
	if (!data)
		return (-1);
	data->arguments = &args;
	data->letter_count = 0;
	data->string_position = first_arg;
	data->min_width = 0;
	data->error = 0;
	while (*(data->string_position) && !data->error)
		ft_check_char(data);
	va_end(args);
	letter_count = (int)data->letter_count;
	if (data->error)
	{
		free(data);
		return (-1);
	}
	free(data);
	return (letter_count);
}
