/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:00:50 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/13 10:41:12 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** create an image made of data addresses where the info about each pixel
** is stored. This allows to manage the expose properly with mlx_loop
** and not have to recalculate when the window is reduced or partially hidden.
*/
t_mlx_img	*create_mlx_image(t_env *env, int width, int height)
{
	t_mlx_img	*img;

	img = (t_mlx_img *)malloc(sizeof(t_mlx_img));
	if (!img)
		error_msg("create_mlx_image failed!");
	img->width = width;
	img->height = height;
	img->img = mlx_new_image(env->mlx->mlx_ptr, img->width, img->height);
	if (!img->img)
		error_msg("mlx_new_image failed!");
	img->d_addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, \
		&img->endian);
	if (!img->d_addr)
		error_msg("mlx_get_data_addr failed!");
	img->bpp /= 8;
	return (img);
}

void	put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	*(int *)(img->d_addr + (((y * img->width) + x) * img->bpp)) = c;
}

/*
** EXIT messages is different depending on error occurence
*/
void	error_msg(char *message)
{
	ft_putstr("error: ");
	ft_putstr(message);
	ft_putstr("\n");
	exit(EXIT_FAILURE);
}
