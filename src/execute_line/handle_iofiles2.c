/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_iofiles2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:39:08 by marschul          #+#    #+#             */
/*   Updated: 2024/01/15 15:34:58 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
tmp file is being opened in the tmp directory and user subdirectory 
within it. /tmp/***REMOVED***/minishell_tmp
 */
bool	get_tmp_name(char tmp_name[PATH_MAX])
{
	char	*name;
	int		length;

	length = 0;
	if (ft_memcpy(tmp_name, "/tmp/", 5) == NULL)
		return (error_wrapper_bool("Minishell: get_tmp_name"));
	length += 5;
	name = getenv("USER");
	if (name == NULL || ft_strlen(name) > PATH_MAX - 20)
		return (error_wrapper_bool("Minishell: get_tmp_name"));
	if (ft_memcpy(tmp_name + length, name, ft_strlen(name)) == NULL)
		return (error_wrapper_bool("Minishell: get_tmp_name"));
	length += ft_strlen(name);
	if (ft_memcpy(tmp_name + length, "/minishell_tmp", 14) == NULL)
		return (error_wrapper_bool("Minishell: get_tmp_name"));
	length += 14;
	tmp_name[length] = '\0';
	return (true);
}
