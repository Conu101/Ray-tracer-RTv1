/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:22:47 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/17 02:48:18 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	point_on_ray(t_ray *r, double t)
{
	t_vec3	p;

	p = ft_add_vec3(r->origin, ft_mul_vec3(r->direction, t));
	return (p);
}

void	init_raycasthit(t_hit *hit)
{
	hit->point = ft_make_vec3(0, 0, 0);
	hit->normal = ft_make_vec3(0, 0, 0);
	hit->object = NULL;
	hit->t = 0.0;
	hit->t2 = 0.0;
	hit->distance = 0.0;
	hit->color = ft_make_rgba(0.0, 0.0, 0.0, 1.0);
}

/*
** see https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-
** to-ray-tracing/implementing-the-raytracing-algorithm
** This is the main trace function. It takes a ray as argument (defined by its 
** origin and direction). We test if this ray intersects any of the objects in 
** the scene. If the ray intersects an object, we compute the intersection 
** point, the normal at the intersection point, and shade this point using this 
** information. Shading depends on the surface property (is it transparent, 
** reflective, diffuse). The function returns a color for the ray. If the ray 
** intersects an object that is the color of the object at the intersection 
** point, otherwise it returns the background color.
*/
int	trace(t_ray *ray, t_scene *scene, t_hit *hit, int stop_at_first)
{
	t_hit	cur_hit;
	double	min_dist;
	int		i;
	int		hit_found;

	min_dist = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_objects)
	{
		if (intersects_object(ray, &scene->objects[i], &cur_hit))
		{
			if (stop_at_first)
				return (TRUE);
			hit_found = TRUE;
			if (cur_hit.distance < min_dist)
			{
				*hit = cur_hit;
				min_dist = cur_hit.distance;
			}
		}
		i++;
	}
	return (hit_found);
}

/*
** final color determination function:
** The further the object, the higher the attenuation
** final color is obtained adding the specular, diffuse and ambient colors.
*/
static t_rgba	shade(t_scene *scene, t_hit *hit)
{
	t_color_data	color;
	int				i;

	init_color_data(&color, scene, hit);
	i = 0;
	while (i < scene->num_lights)
	{
		color.attenuation = 1.0 - (hit->distance / MAX_DISTANCE);
		if (!is_in_shadow(&scene->lights[i], scene, hit))
		{
			color.diffuse = ft_add_rgba(color.diffuse, \
				calc_diffuse(&scene->lights[i], hit));
			color.specular = ft_add_rgba(color.specular, \
				calc_specular(&scene->lights[i], hit, scene->camera.pos));
		}
		color.diffuse = ft_mul_rgba(color.diffuse, color.attenuation);
		color.specular = ft_mul_rgba(color.specular, color.attenuation);
		i++;
	}
	color.out = ft_add_rgba(color.ambient, ft_add_rgba(\
		ft_mul_rgba_rgba(hit->object->color, color.diffuse), color.specular));
	return (color.out);
}

/*
** the ray sent back will be either the color of the ambient scene if the 
** ray did not intersect with any object, or a different color determined by 
** the fn shade otherwise.
** We clamp to keep all values within valid range [0, 1]
*/
t_rgba	raycast(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_rgba	color;

	color = scene->ambient_color;
	if (trace(ray, scene, hit, FALSE))
		color = shade(scene, hit);
	return (ft_clamp_rgba(color));
}
