/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_rgba.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:24:01 by ctrouve           #+#    #+#             */
/*   Updated: 2022/09/21 19:31:05 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

static double	ft_clamp_d(double d, double min, double max)
{
	if (d < min)
		d = min;
	if (d > max)
		d = max;
	return (d);
}

t_rgba	ft_clamp_rgba(t_rgba c)
{
	c.r = ft_clamp_d(c.r, 0.0, 1.0);
	c.g = ft_clamp_d(c.g, 0.0, 1.0);
	c.b = ft_clamp_d(c.b, 0.0, 1.0);
	c.a = ft_clamp_d(c.a, 0.0, 1.0);
	return (c);
}
