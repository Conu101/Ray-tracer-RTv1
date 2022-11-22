/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:35:58 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/17 15:21:05 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	calc_cylinder_normal(t_object *c, t_hit *hit)
{
	t_vec3	cyl_dir;
	t_vec3	c_to_hit;
	t_vec3	v;
	double	d;

	cyl_dir = ft_normalize_vec3(ft_sub_vec3(c->end, c->start));
	c_to_hit = ft_sub_vec3(hit->point, c->start);
	d = ft_dot_vec3(cyl_dir, c_to_hit);
	v = ft_add_vec3(c->start, ft_mul_vec3(cyl_dir, d));
	return (ft_normalize_vec3(ft_sub_vec3(hit->point, v)));
}

void	rotate_cylinder(t_object *c, t_vec3 rot)
{
	t_vec3	res;
	t_vec3	v;

	v = ft_make_vec3(0, 1, 0);
	res = ft_rotate_vec3(v, rot);
	c->end = ft_add_vec3(c->position, res);
	c->start = c->position;
}

int	intersects_cylinder(t_ray *ray, t_object *cyl, t_hit *hit)
{
	t_quadratic	q;
	t_vec3		cyl_vec;
	t_vec3		cam_cyl;
	t_vec3		ray_cyl;

	cyl_vec = ft_sub_vec3(cyl->start, cyl->end);
	cam_cyl = ft_cross_vec3(ft_sub_vec3(ray->origin, cyl->end), cyl_vec);
	ray_cyl = ft_cross_vec3(ray->direction, cyl_vec);
	q.a = ft_dot_vec3(ray_cyl, ray_cyl);
	q.b = 2 * ft_dot_vec3(ray_cyl, cam_cyl);
	q.c = ft_dot_vec3(cam_cyl, cam_cyl) - ((cyl->radius) * (cyl->radius) * \
		ft_dot_vec3(cyl_vec, cyl_vec));
	if (solve_quadratic(q, &hit->t, &hit->t2))
	{
		if (hit->t < 0 || (hit->t2 > 0 && hit->t2 < hit->t))
			hit->t = hit->t2;
		if (hit->t < 0 || hit->t > MAX_DISTANCE)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->normal = calc_cylinder_normal(cyl, hit);
		if (ft_dot_vec3(ray->direction, hit->point) > 3 && ray->shad == TRUE)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
