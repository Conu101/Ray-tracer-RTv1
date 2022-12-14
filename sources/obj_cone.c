/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:35:18 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/13 10:41:38 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** normal vector is perpendicular and opposed to the surface of the cone at the 
** hit point.
*/
static t_vec3	calc_cone_normal(t_object *cone, t_hit *hit)
{
	t_vec3	n;
	t_vec3	cp;
	t_vec3	cone_dir;

	cone_dir = ft_normalize_vec3(ft_sub_vec3(cone->end, cone->start));
	cp = ft_sub_vec3(hit->point, cone->position);
	n = ft_sub_vec3(cp, ft_mul_vec3(cone_dir, \
		(ft_len_vec3(cp) / cos(cone->radius))));
	n = ft_normalize_vec3(n);
	return (n);
}

/*
** we apply rot rotation to the view vector and add it to the position vector 
** of the cone to get its new end vector. New start vector becomes the position 
** vector.
*/
void	rotate_cone(t_object *c, t_vec3 rot)
{
	t_vec3	res;
	t_vec3	v;

	v = ft_make_vec3(0, -1, 0);
	res = ft_rotate_vec3(v, rot);
	c->end = ft_add_vec3(c->position, res);
	c->start = c->position;
}

static int	test_truncated(t_object *cone, t_hit *hit)
{
	if (cone->scale.y != 0 && ft_len_vec3(ft_sub_vec3(hit->point, \
		cone->position)) > cone->scale.y)
		return (FALSE);
	return (TRUE);
}

/*
** from: https://www.shadertoy.com/view/MtcXWr wih maths detailed in:
** http://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
*/
int	intersects_cone(t_ray *ray, t_object *cone, t_hit *hit)
{
	t_quadratic	q;
	t_vec3		x;
	t_vec3		cone_dir;

	cone_dir = ft_normalize_vec3(ft_sub_vec3(cone->end, cone->start));
	x = ft_sub_vec3(ray->origin, cone->position);
	q.a = ft_dot_vec3(ray->direction, cone_dir);
	q.a = ft_dot_vec3(ray->direction, ray->direction) - \
		(1 + cone->radius * cone->radius) * q.a * q.a;
	q.b = 2.0 * (ft_dot_vec3(ray->direction, x) - \
		(1 + cone->radius * cone->radius) \
		* ft_dot_vec3(ray->direction, cone_dir) * ft_dot_vec3(x, cone_dir));
	q.c = ft_dot_vec3(x, cone_dir);
	q.c = ft_dot_vec3(x, x) - (1 + cone->radius * cone->radius) * q.c * q.c;
	if (solve_quadratic(q, &hit->t, &hit->t2) && (hit->t > 0) && \
		(hit->t < MAX_DISTANCE))
	{
		hit->point = point_on_ray(ray, hit->t);
		hit->normal = calc_cone_normal(cone, hit);
		if ((ft_dot_vec3(ft_sub_vec3(hit->point, cone->position), \
			cone_dir) < 0))
			return (FALSE);
		return (test_truncated(cone, hit));
	}
	return (FALSE);
}
