/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:00:09 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/16 17:50:14 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Translation : pos parameter modified, then render
** rotation parameters modified first, then sent to rotate_<object>() fns
*/
static void	handle_obj_rotation(t_object *o, int key)
{
	if (key == KEY_PAD_1)
		o->rotation.z -= 1.0;
	else if (key == KEY_PAD_2)
		o->rotation.z += 1.0;
	else if (key == KEY_PAD_3)
		o->rotation.x -= 1.0;
	else if (key == KEY_PAD_4)
		o->rotation.x += 1.0;
	else if (key == KEY_PAD_5)
		o->rotation.y -= 1.0;
	else if (key == KEY_PAD_6)
		o->rotation.y += 1.0;
	if (o->type == CYLINDER)
		rotate_cylinder(o, o->rotation);
	if (o->type == PLANE)
		rotate_plane(o, o->rotation);
	if (o->type == CONE)
		rotate_cone(o, o->rotation);
}

static void	handle_object_manipulation(t_object *o, int key)
{
	if (key == KEY_PAD_7)
		o->position.x -= 1.0;
	else if (key == KEY_PAD_8)
		o->position.x += 1.0;
	else if (key == KEY_PAD_9)
		o->position.y -= 1.0;
	else if (key == KEY_PAD_0)
		o->position.y += 1.0;
	else if (key == KEY_PAD_MINUS)
		o->position.z -= 1.0;
	else if (key == KEY_PAD_PLUS)
		o->position.z += 1.0;
	handle_obj_rotation(o, key);
}

static void	handle_light_position(t_light *l, int key)
{
	if (key == KEY_PAD_7)
		l->position.x -= 1.0;
	else if (key == KEY_PAD_8)
		l->position.x += 1.0;
	else if (key == KEY_PAD_9)
		l->position.y -= 1.0;
	else if (key == KEY_PAD_0)
		l->position.y += 1.0;
	else if (key == KEY_PAD_MINUS)
		l->position.z -= 1.0;
	else if (key == KEY_PAD_PLUS)
		l->position.z += 1.0;
}

static void	handle_light_manipulation(t_light *l, int key)
{
	if (key == KEY_J)
		l->intensity -= 0.1;
	else if (key == KEY_K)
		l->intensity += 0.1;
	if (l->type == DIRECTIONAL)
	{
		if (key == KEY_PAD_1)
			l->rotation.z -= 1.0;
		else if (key == KEY_PAD_2)
			l->rotation.z += 1.0;
		else if (key == KEY_PAD_3)
			l->rotation.x -= 1.0;
		else if (key == KEY_PAD_4)
			l->rotation.x += 1.0;
		else if (key == KEY_PAD_5)
			l->rotation.y -= 1.0;
		else if (key == KEY_PAD_6)
			l->rotation.y += 1.0;
		rotate_light(l, l->rotation);
	}
	else if (l->type == POINT)
		handle_light_position(l, key);
}

/*
** Only main keypad commands in this program (no use of key nums!) to be 
** laptop-friendly :)
** After modifying parameters, triggers render.c in rtv1.c
*/
int	key_press(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (key == KEY_ESC)
		del_env_exit(env);
	else if (key == KEY_SPACE)
		update(param);
	else if (key == KEY_PAD_LEFT || key == KEY_PAD_RIGHT || key == \
		KEY_PAD_DOWN || key == KEY_PAD_UP || key == KEY_INF || key == KEY_SUP)
		handle_camera_movement(env, key);
	else if (key == KEY_O || key == KEY_L)
		select_object_or_light(key, env);
	if (env->scene->selected_object)
		handle_object_manipulation(env->scene->selected_object, key);
	if (env->scene->selected_light)
		handle_light_manipulation(env->scene->selected_light, key);
	render(env, env->scene);
	return (0);
}
