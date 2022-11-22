/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:38:00 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:21:32 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	ft_len_vec3(t_vec3 v)
{
	double	l;

	if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f)
		return (0.0f);
	l = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (l);
}
