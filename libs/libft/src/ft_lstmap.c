/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:00:23 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/10 11:38:59 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_success(void *check, t_list **start, void (*del)(void *))
{
	if (!check)
	{
		ft_lstclear(start, del);
		return (0);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_iter;
	t_list	*new_list_start;

	new_list_start = malloc(sizeof(t_list));
	if (!new_list_start || !f || !del || !lst)
		return (NULL);
	new_list_iter = new_list_start;
	while (lst)
	{
		new_list_iter->content = f(lst->content);
		if (lst->next)
			new_list_iter->next = malloc(sizeof(t_list));
		else
		{
			new_list_iter->next = NULL;
			return (new_list_start);
		}
		if (!check_success(new_list_iter->next, &new_list_start, del))
			return (NULL);
		new_list_iter = new_list_iter->next;
		lst = lst->next;
	}
	return (NULL);
}
