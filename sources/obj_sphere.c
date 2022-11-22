/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:37:50 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/17 15:31:10 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	intersects_sphere(t_ray *ray, t_object *sphere, t_hit *hit)
{
	t_quadratic	q;
	t_vec3		sph_vec;

	sph_vec = ft_sub_vec3(ray->origin, sphere->position);
	q.a = ft_dot_vec3(ray->direction, ray->direction);
	q.b = 2.0 * ft_dot_vec3(sph_vec, ray->direction);
	q.c = ft_dot_vec3(sph_vec, sph_vec) - (sphere->radius) * (sphere->radius);
	if (solve_quadratic(q, &hit->t, &hit->t2))
	{
		if (hit->t > hit->t2)
			ft_swap_d(&hit->t, &hit->t2);
		if (hit->t < 0)
		{
			hit->t = hit->t2;
			if (hit->t < 0)
				return (FALSE);
		}
		if (hit->t > MAX_DISTANCE)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->normal = ft_normalize_vec3(ft_sub_vec3(hit->point, \
			sphere->position));
		return (TRUE);
	}
	return (FALSE);
}
