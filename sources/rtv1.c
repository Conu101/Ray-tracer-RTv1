/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:51:34 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/21 14:57:44 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	render(t_env *env, t_scene *scene)
{
	t_ray	ray;
	t_vec2	screen;
	t_vec2i	cur;
	t_hit	hit;

	update_camera(&scene->camera, scene->camera.pos, scene->camera.dir, \
		scene->camera.fov);
	cur.y = 0;
	while (cur.y < env->height)
	{
		cur.x = 0;
		while (cur.x < env->width)
		{
			screen.x = (double)cur.x / (double)SCREEN_WIDTH;
			screen.y = (double)cur.y / (double)SCREEN_HEIGHT;
			ray = get_camera_ray(&env->scene->camera, screen.x, screen.y);
			put_pixel_mlx_img(env->mlx_img, cur.x, cur.y, \
				ft_get_color(raycast(&ray, env->scene, &hit)));
			cur.x++;
		}
		cur.y++;
	}
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr, \
		env->mlx_img->img, 0, 0);
}

static int	display_controls(char *window_title)
{
	ft_putstr(window_title);
	ft_putstr("\n\n");
	ft_putstr("RTv1 is a ray tracing program displaying simple shapes coded in \
a text file passed as argument.\n\
Camera, objects and lights parameters can be modified by updating the \
parameters file or with the following commands:\n\
- Camera movement (x, y, z): press keys 'left', 'right', 'down', 'up', \
'<', '>'\n\
- Select object: press 'O'\n\
- Select light: press 'L'\n\
- Light intensity (-/+): press keys 'J' and 'K'\n\
- Object/light rotation (z, x, y): press keys from '1' to '6'\n\
- Object/light translation (x, y, z): press keys from '7' to '+'\n\
- Update rendering after modifying parameters file: press 'space'.\n\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	*env;
	char	*window_title;

	if (argc != 2)
	{
		ft_putstr("usage: ./rtv1 <scene file>\n");
		return (1);
	}
	window_title = ft_strjoin("RTv1 by Conu - ", argv[1]);
	if (!window_title)
		error_msg("Window title: ft_strjoin failed");
	env = init_env(SCREEN_WIDTH, SCREEN_HEIGHT, window_title);
	if (!read_scene(env->scene, argv[1]))
	{
		error_msg("Scene could not be read, read_scene failed.");
		return (1);
	}
	display_controls(window_title);
	render(env, env->scene);
	mlx_hook(env->mlx->win_ptr, 2, (1L << 0), key_press, (void *)env);
	mlx_hook(env->mlx->win_ptr, 17, 0, close_window, (void *)env);
	mlx_loop(env->mlx->mlx_ptr);
	return (0);
}
