/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:00:09 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/17 14:26:53 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Info message prints out in the command line everytime the key 'O' or 'L' is
** pressed, to inform on the currently selected object or light that can be
** modified "live".
*/

static const char	*obj_type(int type)
{
	const char	*obj_types[4];
	int			i;

	obj_types[0] = "PLANE";
	obj_types[1] = "SPHERE";
	obj_types[2] = "CYLINDER";
	obj_types[3] = "CONE";
	i = 0;
	while (i < 4)
	{
		if (i == type)
			return (obj_types[i]);
		i++;
	}
	return (NULL);
}

static void	print_info(int i, t_env *env)
{
	if (env->scene->selected_object)
	{
		ft_putstr("Selected object index ");
		ft_putnbr(i);
		ft_putstr(" of type ");
		ft_putstr(obj_type(env->scene->selected_object->type));
		ft_putchar('\n');
	}
	if (env->scene->selected_light)
	{
		ft_putstr("Selected light index ");
		ft_putnbr(i);
		ft_putstr(" of type ");
		ft_putnbr(env->scene->selected_light->type);
		ft_putchar('\n');
		ft_putstr("Types :\n0 = directionnal\n1 = point\n\n");
	}
}

/*
** Next object selected until we've gone through all objects. To re-initialize, 
** press 'L' for lights and the selected object will be set to NULL.
*/
static int	select_obj(t_env *env)
{
	int	i;

	i = 0;
	if (env->scene->selected_object == NULL)
	{
		env->scene->selected_object = &env->scene->objects[i];
		print_info(i, env);
	}
	else
	{
		while (i < env->scene->num_objects - 1)
		{
			if (env->scene->selected_object == &env->scene->objects[i])
			{
				env->scene->selected_object = &env->scene->objects[i + 1];
				print_info(i + 1, env);
				return (1);
			}
			i++;
		}
		ft_putstr("\nBack to first selected object:\n\n");
		env->scene->selected_object = NULL;
		select_obj(env);
	}
	return (0);
}

/*
** Same principle with the lights as with the objects.
*/
static int	select_light(t_env *env)
{
	int	i;

	i = 0;
	if (env->scene->selected_light == NULL)
	{
		env->scene->selected_light = &env->scene->lights[0];
		print_info(i, env);
	}
	else
	{
		while (i < env->scene->num_lights - 1)
		{
			if (env->scene->selected_light == &env->scene->lights[i])
			{
				env->scene->selected_light = &env->scene->lights[i + 1];
				print_info(i + 1, env);
				return (1);
			}
			i++;
		}
		ft_putstr("Back to first selected light:\n\n");
		env->scene->selected_light = NULL;
		select_light(env);
	}
	return (0);
}

void	select_object_or_light(int key, t_env *env)
{
	if (key == KEY_O)
	{
		env->scene->selected_light = NULL;
		select_obj(env);
	}
	else if (key == KEY_L)
	{
		env->scene->selected_object = NULL;
		select_light(env);
	}
}
