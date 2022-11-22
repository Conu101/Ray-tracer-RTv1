/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:55:03 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/21 14:49:50 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** handle_camera_movement: move camera straight across axis, 
** so both position and direction (shoot angle) are modified.
*/
static void	handle_camera_movement_bis(t_env *env, int key)
{
	if (key == KEY_INF)
	{
		env->scene->camera.pos.z -= 1.0;
		env->scene->camera.dir.z -= 1.0;
	}
	else if (key == KEY_SUP)
	{
		env->scene->camera.pos.z += 1.0;
		env->scene->camera.dir.z += 1.0;
	}
}

void	handle_camera_movement(t_env *env, int key)
{
	if (key == KEY_PAD_LEFT)
	{
		env->scene->camera.dir.x -= 1.0;
		env->scene->camera.pos.x -= 1.0;
	}
	else if (key == KEY_PAD_RIGHT)
	{
		env->scene->camera.dir.x += 1.0;
		env->scene->camera.pos.x += 1.0;
	}
	else if (key == KEY_PAD_UP)
	{
		env->scene->camera.pos.y += 1.0;
		env->scene->camera.dir.y += 1.0;
	}
	else if (key == KEY_PAD_DOWN)
	{
		env->scene->camera.pos.y -= 1.0;
		env->scene->camera.dir.y -= 1.0;
	}
	else if (key == KEY_INF || key == KEY_SUP)
		handle_camera_movement_bis(env, key);
}

/*
** initialize all camera fields
** ft_normalize_vec3 returns the vector divided by its length:
** l = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)) -> this way we obtain
** a direction.
** see : https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing\
** -generating-camera-rays
*/
int	update_camera(t_camera *cam, t_vec3 pos, t_vec3 dir, double fov)
{
	t_camera_info	ci;

	cam->pos = pos;
	cam->dir = dir;
	cam->fov = fov;
	cam->aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	ci.v_up = ft_make_vec3(0, 1, 0.001);
	ci.w = ft_normalize_vec3(ft_sub_vec3(cam->pos, cam->dir));
	ci.u = ft_normalize_vec3(ft_cross_vec3(ci.v_up, ci.w));
	ci.v = ft_cross_vec3(ci.w, ci.u);
	ci.theta = ft_deg_to_rad(cam->fov);
	ci.half_height = tan(ci.theta / 2.0);
	ci.half_width = cam->aspect * ci.half_height;
	cam->lower_left_corner = ft_sub_vec3(cam->pos, \
	ft_sub_vec3(ft_mul_vec3(ci.u, ci.half_width), \
	ft_sub_vec3(ft_mul_vec3(ci.v, ci.half_height), ci.w)));
	cam->horizontal = ft_mul_vec3(ci.u, ci.half_width * 2);
	cam->vertical = ft_mul_vec3(ci.v, ci.half_height * 2);
	return (1);
}

/*
** the ray comes from the camera and its direction is the normalized vector
** between the camera position and the pt of coord(u, v) = (screen.x, screen.y)
*/
t_ray	get_camera_ray(t_camera *camera, double u, double v)
{
	t_ray	ray;

	ray.origin_object = NULL;
	ray.origin = camera->pos;
	ray.direction = ft_normalize_vec3(ft_sub_vec3(ft_add_vec3(camera->\
	lower_left_corner, ft_add_vec3(ft_mul_vec3(camera->horizontal, u), \
	ft_mul_vec3(camera->vertical, -v))), ray.origin));
	ray.shad = FALSE;
	return (ray);
}

/*
** Get the coordinates on the screen point from a world point depending on 
** camera info.
*/
t_vec2i	world_to_screen_point(t_camera *camera, t_vec3 wp)
{
	t_vec3	dir;
	t_vec2i	sp;

	dir = ft_normalize_vec3(ft_sub_vec3(wp, camera->pos));
	sp.x = ((dir.x + camera->aspect * 0.5) / camera->aspect) * SCREEN_WIDTH;
	sp.y = SCREEN_HEIGHT - ((dir.y + 0.5) * SCREEN_HEIGHT);
	return (sp);
}
