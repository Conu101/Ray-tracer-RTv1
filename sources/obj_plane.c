/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:37:08 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/17 01:14:55 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotate_plane(t_object *p, t_vec3 rot)
{
	t_vec3	res;
	t_vec3	v;

	v = ft_make_vec3(0, 1, 0);
	res = ft_rotate_vec3(v, rot);
	p->normal = ft_normalize_vec3(res);
}

static int	test_quad(t_hit *hit, t_object *plane)
{
	if (hit->point.x > plane->position.x + (plane->scale.x / 2.0) || \
		hit->point.x < plane->position.x - (plane->scale.x / 2.0))
		return (FALSE);
	if (hit->point.z > plane->position.z + (plane->scale.z / 2.0) || \
		hit->point.z < plane->position.z - (plane->scale.z / 2.0))
		return (FALSE);
	if (hit->point.y > plane->position.y + (plane->scale.y / 2.0) || \
		hit->point.y < plane->position.y - (plane->scale.y / 2.0))
		return (FALSE);
	return (TRUE);
}

/*
** From https://www.shadertoy.com/view/MtcXWr
*/
int	intersects_plane(t_ray *ray, t_object *plane, t_hit *hit)
{
	double	t;
	double	d;

	d = ft_dot_vec3(plane->normal, ray->direction);
	if (ray->origin_object && d < 0.0001)
		return (FALSE);
	t = ft_dot_vec3(ft_sub_vec3(plane->position, ray->origin), \
		plane->normal) / d;
	if (t > 0.0001 && t < MAX_DISTANCE)
	{
		hit->t = t;
		hit->point = point_on_ray(ray, hit->t);
		hit->object = plane;
		hit->normal = plane->normal;
		if (plane->scale.x > 0 && plane->scale.y > 0 && plane->scale.z > 0)
			return (test_quad(hit, plane));
		return (TRUE);
	}
	return (FALSE);
}
