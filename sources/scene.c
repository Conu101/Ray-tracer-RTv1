/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:48 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/21 17:22:21 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_obj_type	parse_object_type(char *line)
{
	if (ft_strequ(line, "PLANE"))
		return (PLANE);
	if (ft_strequ(line, "SPHERE"))
		return (SPHERE);
	if (ft_strequ(line, "CYLINDER"))
		return (CYLINDER);
	if (ft_strequ(line, "CONE"))
		return (CONE);
	if (ft_strequ(line, "LIGHT"))
		return (LIGHT);
	if (ft_strequ(line, "CAMERA"))
		return (CAMERA);
	return (-1);
}

static void	init_scene(t_scene *scene, char *path, int fd)
{
	scene->ambient_color = ft_make_rgba(0, 0, 0, 1);
	scene->a_color_read = 0;
	scene->num_lights = 0;
	scene->lights = NULL;
	scene->num_objects = 0;
	scene->objects = NULL;
	scene->path = path;
	scene->selected_object = NULL;
	scene->l_index = 0;
	scene->o_index = 0;
	scene->selected_light = NULL;
	scene->fd = fd;
}

/*
** For now we fix the ambient color to black, to be modified for RT.
*/
static void	parse_scene_header(char *line, t_scene *scene)
{
	if (ft_strnequ(line, "OBJECTS", 6) && !scene->num_objects)
	{
		scene->num_objects = ft_atoi(line + 7);
		scene->objects = (t_object *)malloc(sizeof(t_object) \
		* scene->num_objects);
		if (!scene->objects)
			error_msg("malloc of scene->objects failed");
	}
	else if (ft_strnequ(line, "LIGHTS", 5) && !scene->num_lights)
	{
		scene->num_lights = ft_atoi(line + 6);
		scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights);
		if (!scene->lights)
			error_msg("malloc of scene->lights failed");
	}
	else if (ft_strnequ(line, "COLOR", 5))
	{
		scene->ambient_color = ft_make_rgba(0, 0, 0, 1);
		scene->a_color_read = 1;
	}
}

static void	select_parsing(int fd, t_obj_type type, t_scene *sc)
{
	if (type == LIGHT)
		parse_light(fd, &(sc->lights)[sc->l_index++]);
	else if (type == CAMERA)
		parse_camera(fd, &sc->camera);
	else if (type >= 0 && type < 4)
		parse_object(fd, type, &(sc->objects)[sc->o_index++]);
}

/*
** parameter file is read: camera, all objects and lights set 
** final check to see if lights and objects index corresponds to the
** numbers announced in the file header.
*/
int	read_scene(t_scene *sc, char *path)
{
	int			fd;
	char		*line;
	t_obj_type	type;

	fd = open(path, O_RDWR);
	if (fd < 3)
		error_msg("error opening scene file");
	if (check_dash(path) == 0)
		error_msg("the last line of the param file should be one only '#' !");
	init_scene(sc, path, fd);
	while (get_next_line(fd, &line))
	{
		if (!sc->num_objects || !sc->num_lights || !sc->a_color_read)
			parse_scene_header(line, sc);
		else
		{
			type = parse_object_type(line);
			select_parsing(fd, type, sc);
		}
		free(line);
	}
	close(fd);
	if (sc->num_lights == sc->l_index && sc->num_objects == sc->o_index)
		return (1);
	return (0);
}
