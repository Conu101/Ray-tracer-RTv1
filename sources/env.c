/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:58:59 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/21 18:33:26 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env	*init_env(int width, int height, char *title)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		error_msg("env malloc failed");
	env->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!env->mlx)
		error_msg("env->mlx malloc failed");
	env->width = width;
	env->height = height;
	env->mlx->mlx_ptr = mlx_init();
	if (!env->mlx->mlx_ptr)
		error_msg("Error: failed mlx_init");
	env->mlx->win_ptr = mlx_new_window(env->mlx->mlx_ptr, width, height, title);
	if (!env->mlx->win_ptr)
		error_msg("Error: failed mlx_new_window");
	env->mlx_img = create_mlx_image(env, width, height);
	env->scene = (t_scene *)malloc(sizeof(t_scene));
	if (!env->scene)
		error_msg("env->scene malloc failed");
	env->scene->fd = 0;
	return (env);
}

/*
** function triggered by key press ESC
*/
void	del_env_exit(t_env *env)
{
	free(env->scene->lights);
	free(env->scene->objects);
	free(env->scene);
	mlx_destroy_image(env->mlx->mlx_ptr, env->mlx_img->img);
	mlx_destroy_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
	free(env->mlx_img);
	free(env->mlx);
	free(env);
	exit(EXIT_SUCCESS);
}

/*
** function triggered by top left cross to close window
*/
int	close_window(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}

int	update(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (!param || !env || !env->scene)
		return (1);
	ft_putstr("The scene was updated\n\n");
	free(env->scene->lights);
	free(env->scene->objects);
	if (env->scene->fd > 0)
		close(env->scene->fd);
	if (read_scene(env->scene, env->scene->path))
		render(env, env->scene);
	else
		error_msg("Failed to read scene!\n");
	return (1);
}
