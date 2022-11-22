/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_vec3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:38:40 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:24:13 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	ft_normalize_vec3(t_vec3 v)
{
	t_vec3	new;
	double	l;

	l = ft_len_vec3(v);
	new = ft_div_vec3(v, l);
	return (new);
}
