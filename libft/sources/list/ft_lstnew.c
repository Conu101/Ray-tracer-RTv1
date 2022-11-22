/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:13:45 by ctrouve           #+#    #+#             */
/*   Updated: 2022/04/06 12:13:47 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*fill_list(t_list **list,
		void const *content, size_t content_size)
{
	(*list)->content = (void *)malloc(content_size);
	if (!(*list)->content)
	{
		free(*list);
		return (NULL);
	}
	ft_memcpy((*list)->content, content, content_size);
	(*list)->content_size = content_size;
	return (*list);
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->next = NULL;
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
		return (list);
	}
	return (fill_list(&list, content, content_size));
}
