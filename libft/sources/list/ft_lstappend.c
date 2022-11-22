/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:56:46 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:20:23 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*cur_element;

	if (*alst)
	{
		cur_element = *alst;
		while (cur_element->next)
		{
			cur_element = cur_element->next;
		}
		cur_element->next = new;
	}
	else
	{
		*alst = new;
	}
}
