/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp_rgba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:24:23 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/11 23:59:50 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

static double	ft_lerp_d(double n1, double n2, double t)
{
	return (n1 + (n2 - n1) * t);
}

t_rgba	ft_lerp_rgba(t_rgba c1, t_rgba c2, double t)
{
	t_rgba	color;

	color.r = ft_lerp_d(c1.r, c2.r, t);
	color.g = ft_lerp_d(c1.g, c2.g, t);
	color.b = ft_lerp_d(c1.b, c2.b, t);
	color.a = ft_lerp_d(c1.a, c2.a, t);
	return (color);
}
