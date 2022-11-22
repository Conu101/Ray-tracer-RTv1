/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflect_vec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:38:58 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:21:20 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	ft_reflect_vec3(t_vec3 v, t_vec3 n)
{
	t_vec3	r;

	n = ft_normalize_vec3(n);
	r = ft_sub_vec3(v, ft_mul_vec3(n, 2.0f * ft_dot_vec3(v, n)));
	return (r);
}
