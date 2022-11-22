/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:03:20 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/17 14:30:01 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** By default light is white, directional (similar to day light through a 
** window, there is not one only origin of ray) and directed towards origin 
** of scene.
*/
void	init_light(t_light *light)
{
	light->type = 0;
	light->position = ft_make_vec3(0, 0, 0);
	light->direction = ft_make_vec3(0, -1, 0);
	light->color = ft_make_rgba(1, 1, 1, 1);
	light->intensity = 1.0;
}

void	rotate_light(t_light *light, t_vec3 rot)
{
	t_vec3	res;
	t_vec3	v;

	v = ft_make_vec3(0, -1, 0);
	res = ft_rotate_vec3(v, rot);
	light->direction = ft_normalize_vec3(res);
}

/*
** returns 0 or 1 depending if the ray hits a shadow
** 
*/
int	is_in_shadow(t_light *light, t_scene *scene, t_hit *origin)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = ft_add_vec3(origin->point, \
		ft_mul_vec3(ft_normalize_vec3(origin->normal), SHADOW_ACNE));
	shadow_ray.origin_object = origin->object;
	shadow_ray.shad = TRUE;
	if (light->type == POINT)
	{
		shadow_ray.direction = ft_normalize_vec3((ft_sub_vec3(light->position, \
			shadow_ray.origin)));
	}
	else
		shadow_ray.direction = \
			ft_normalize_vec3(ft_mul_vec3(light->direction, -1.0));
	if (trace(&shadow_ray, scene, &hit, TRUE) && \
		hit.object != shadow_ray.origin_object)
		return (TRUE);
	return (FALSE);
}

/*
** see https://raytracing.github.io/books/RayTracingInOneWeekend.html#
** diffusematerials/asimplediffusematerial
** 
** Diffuse objects that don’t emit light merely take on the color of their 
** surroundings, but they modulate that with their own intrinsic color. Light 
** that reflects off a diffuse surface has its direction randomized.
*/
t_rgba	calc_diffuse(t_light *light, t_hit *hit)
{
	t_rgba	diffuse;
	t_vec3	light_dir;
	double	ndotl;

	if (light->type == POINT)
		light_dir = ft_normalize_vec3(ft_sub_vec3(light->position, hit->point));
	else
		light_dir = ft_normalize_vec3(ft_mul_vec3(light->direction, -1.0));
	ndotl = ft_dot_vec3(hit->normal, light_dir);
	diffuse = ft_mul_rgba(light->color, ft_max_d(ndotl, 0.0));
	return (ft_mul_rgba(diffuse, light->intensity));
}

/*
** see https://ogldev.org/www/tutorial19/tutorial19.html
**
** k is the specular exponent (linked to the material), we get shine if the 
** value is positive and no shine (matte surface) for negative values.
**
** r is reflection vector
** c is camera vector
*/
t_rgba	calc_specular(t_light *light, t_hit *hit, t_vec3 cam)
{
	t_rgba			specular;
	t_vec3			light_dir;
	t_vec3			r;
	t_vec3			c;
	unsigned int	k;

	if (light->type == POINT)
		light_dir = ft_normalize_vec3(ft_sub_vec3(light->position, hit->point));
	else
		light_dir = ft_normalize_vec3(ft_mul_vec3(light->direction, -1.0));
	light_dir = ft_mul_vec3(light_dir, -1.0);
	r = ft_normalize_vec3(ft_reflect_vec3(light_dir, hit->normal));
	c = ft_normalize_vec3(ft_sub_vec3(cam, hit->point));
	k = 40;
	specular = ft_mul_rgba(ft_mul_rgba(light->color, light->intensity), \
		pow(ft_max_d(ft_dot_vec3(r, c), 0.0), k));
	return (specular);
}
