/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:36:22 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/13 11:55:46 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_object(t_object *object)
{
	object->type = 0;
	object->position = ft_make_vec3(0.0, 0.0, 0.0);
	object->rotation = ft_make_vec3(0.0, 0.0, 0.0);
	object->scale = ft_make_vec3(0.0, 0.0, 0.0);
	object->normal = ft_make_vec3(0.0, 0.0, 0.0);
	object->color = ft_make_rgba(0.0, 0.0, 0.0, 1.0);
	object->start = ft_make_vec3(0, 0, 0);
	object->end = ft_make_vec3(1, 1, 1);
	object->radius = 0.0;
}

/*
** Initialize hit parameters and assess if there is an intersection
** between the ray and the objects depending on the type of object.
*/
int	intersects_object(t_ray *ray, t_object *object, t_hit *hit)
{
	int	hit_found;

	hit_found = 0;
	hit->distance = 0.0;
	if (object->type == PLANE)
		hit_found = intersects_plane(ray, object, hit);
	else if (object->type == SPHERE)
		hit_found = intersects_sphere(ray, object, hit);
	else if (object->type == CYLINDER)
		hit_found = intersects_cylinder(ray, object, hit);
	else if (object->type == CONE)
		hit_found = intersects_cone(ray, object, hit);
	if (hit_found)
	{
		hit->object = object;
		hit->point = point_on_ray(ray, hit->t);
		hit->distance = hit->t;
	}
	return (hit_found);
}

/*
** see https://www.programiz.com/c-programming/examples/quadratic-roots
** The standard form of a quadratic equation is:
**
** ax2 + bx + c = 0, where
** a, b and c are real numbers and
** a != 0
** The term b2; - 4ac is known as the discriminant of a quadratic equation.
** It tells the nature of the roots.
**
** If the discriminant is greater than 0, the roots are real and different.
** If the discriminant is equal to 0, the roots are real and equal.
** If the discriminant is less than 0, the roots are complex and different.
*/

int	solve_quadratic(t_quadratic q, double *t1, double *t2)
{
	double	d;

	*t1 = -1;
	*t2 = -1;
	d = q.b * q.b - 4 * q.a * q.c;
	if (d == 0)
	{
		*t1 = (-q.b - sqrt(d)) / (2.0 * q.a);
		return (1);
	}
	if (d > 0)
	{
		*t1 = (-q.b - sqrt(d)) / (2.0 * q.a);
		*t2 = (-q.b + sqrt(d)) / (2.0 * q.a);
		return (2);
	}
	return (0);
}

double	ft_deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

void	init_color_data(t_color_data *color, t_scene *scene, t_hit *hit)
{
	color->ambient = ft_mul_rgba(hit->object->color, \
		ft_intensity_rgba(scene->ambient_color));
	color->diffuse = ft_make_rgba(0, 0, 0, 1);
	color->specular = ft_make_rgba(0, 0, 0, 1);
	color->attenuation = 0.0;
}
