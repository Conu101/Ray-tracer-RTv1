/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:38:49 by ctrouve           #+#    #+#             */
/*   Updated: 2022/11/22 16:01:10 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_char_memdel(char **ap)
{
	int	i;

	i = 0;
	while (ap[i])
	{
		free (ap[i]);
		i++;
	}
	free (ap);
}

t_vec3	ft_parsing_vec3(char *str)
{
	t_vec3	v;
	char	**res;

	res = ft_strsplit((const char *)str, ' ');
	if (res[3])
	{
		v.x = ft_strtod(res[1]);
		v.y = ft_strtod(res[2]);
		v.z = ft_strtod(res[3]);
	}
	else
	{
		v = ft_make_vec3(0, 0, 0);
		ft_char_memdel(res);
		error_msg("check amount of vector parameters in file");
	}
	ft_char_memdel(res);
	return (v);
}

t_rgba	ft_parsing_rgba(char *line)
{
	t_rgba	c;
	char	**res;

	res = ft_strsplit((const char *)line, ' ');
	if (res[3])
	{
		c.r = ft_strtod(res[1]);
		c.g = ft_strtod(res[2]);
		c.b = ft_strtod(res[3]);
		c.a = 1.0;
	}
	else
	{
		c = ft_make_rgba(0, 0, 0, 1);
		ft_char_memdel(res);
		error_msg("check amount of color parameters in file");
	}
	ft_char_memdel(res);
	return (c);
}

int	check_dash(char *path)
{
	int		fd;
	int		len;
	char	scene[1001];

	fd = open(path, O_RDWR);
	ft_bzero(scene, 1001);
	read(fd, scene, 1000);
	if (scene[1000] != '\0')
		return (0);
	len = ft_strlen(scene);
	if (scene[len - 1] != '#')
		return (0);
	return (1);
}
