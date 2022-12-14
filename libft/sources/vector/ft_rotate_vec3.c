/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:39:09 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:22:21 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include <math.h>

static double	ft_deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

t_vec3	ft_rotate_vec3(t_vec3 v, t_vec3 rot)
{
	t_vec3	res;

	rot.x = ft_deg_to_rad(rot.x);
	rot.y = ft_deg_to_rad(rot.y);
	rot.z = ft_deg_to_rad(rot.z);
	res.x = v.x;
	res.y = v.y * cos(rot.x) + v.z * sin(rot.x);
	res.z = -v.y * sin(rot.x) + v.z * cos(rot.x);
	v = (t_vec3){res.x, res.y, res.z};
	res.x = v.x * cos(rot.y) + v.z * sin(rot.y);
	res.y = v.y;
	res.z = -v.x * sin(rot.y) + v.z * cos(rot.y);
	v = (t_vec3){res.x, res.y, res.z};
	res.x = v.x * cos(rot.z) - v.y * sin(rot.z);
	res.y = v.x * sin(rot.z) + v.y * cos(rot.z);
	res.z = v.z;
	return (res);
}
