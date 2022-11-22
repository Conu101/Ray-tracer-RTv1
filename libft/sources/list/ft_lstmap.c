/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:13:37 by ctrouve           #+#    #+#             */
/*   Updated: 2022/04/06 12:13:40 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_link(t_list **link)
{
	free((*link)->content);
	free(*link);
	*link = NULL;
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	new = f(lst);
	if (!new)
		return (NULL);
	if (lst->next)
	{
		new->next = ft_lstmap(lst->next, f);
		if (!new->next)
			ft_free_link(&new);
	}
	return (new);
}
