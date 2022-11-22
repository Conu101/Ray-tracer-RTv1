/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:03:44 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/21 18:28:39 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	verify_camera(t_camera *c)
{
	double	len;

	len = ft_len_vec3(ft_sub_vec3(c->pos, c->dir));
	if (len < 0.0001)
		error_msg("Error in verify_camera: check camera pos and dir.");
}

int	parse_camera(int fd, t_camera *camera)
{
	char	*line;
	t_vec3	pos;
	t_vec3	dir;
	double	fov;

	if (!camera)
		error_msg("Error: camera is NULL\n");
	while (get_next_line(fd, &line))
	{
		if (ft_strnequ(line, "pos", 3))
			pos = ft_parsing_vec3(line);
		if (ft_strnequ(line, "fov", 3))
			fov = ft_strtod(ft_strstr(line, " "));
		if (ft_strnequ(line, "dir", 3))
			dir = ft_parsing_vec3(line);
		if (line[0] == '#')
		{
			update_camera(camera, pos, dir, fov);
			verify_camera(camera);
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

int	parse_light(int fd, t_light *light)
{
	char	*line;

	init_light(light);
	while (get_next_line(fd, &line))
	{
		if (ft_strnequ(line, "type", 4))
			light->type = ft_atoi(ft_strstr(line, " "));
		else if (ft_strnequ(line, "pos", 3))
			light->position = ft_parsing_vec3(line);
		else if (ft_strnequ(line, "rot", 3))
			light->rotation = ft_parsing_vec3(line);
		else if (ft_strnequ(line, "col", 3))
			light->color = ft_parsing_rgba(line);
		else if (ft_strnequ(line, "int", 3))
			light->intensity = ft_strtod(line + 4);
		else if (line[0] == '#')
		{
			free(line);
			rotate_light(light, light->rotation);
			return (1);
		}
		free(line);
	}
	return (0);
}

static void	set_object_property(char *line, t_object *object)
{
	if (ft_strnequ(line, "pos", 3))
		object->position = ft_parsing_vec3(line);
	else if (ft_strnequ(line, "rot", 3))
		object->rotation = ft_parsing_vec3(line);
	else if (ft_strnequ(line, "sca", 3))
		object->scale = ft_parsing_vec3(line);
	else if (ft_strnequ(line, "col", 3))
		object->color = ft_parsing_rgba(line);
	else if (ft_strnequ(line, "rad", 3))
		object->radius = ft_strtod(line + 4);
}

int	parse_object(int fd, t_obj_type type, t_object *object)
{
	char	*line;

	if (type < 0 || !object)
		error_msg("Object type could not be read");
	init_object(object);
	while (get_next_line(fd, &line))
	{
		object->type = type;
		if (line[0] != '#')
			set_object_property(line, object);
		else if (line[0] == '#')
		{
			if (type == CYLINDER)
				rotate_cylinder(object, object->rotation);
			if (type == CONE)
				rotate_cone(object, object->rotation);
			if (type == PLANE)
				rotate_plane(object, object->rotation);
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}
