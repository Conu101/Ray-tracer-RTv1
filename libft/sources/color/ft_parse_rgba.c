/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rgba.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:24:48 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/21 00:20:57 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

t_rgba	ft_parse_rgba(char *line)
{
	t_rgba	c;
	char	*token;

	line = ft_strstr(line, " ");
	token = ft_strtok(line, ' ');
	c.r = ft_strtod(token);
	token = ft_strtok(NULL, ' ');
	c.g = ft_strtod(token);
	token = ft_strtok(NULL, ' ');
	c.b = ft_strtod(token);
	c.a = 1.0;
	return (c);
}
