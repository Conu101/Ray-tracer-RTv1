/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:37:25 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:22:57 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	ft_div_vec3(t_vec3 v, double t)
{
	t_vec3	new;

	if (t == 0.0)
		return (v);
	new.x = v.x / t;
	new.y = v.y / t;
	new.z = v.z / t;
	return (new);
}
