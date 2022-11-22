/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:25:27 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/11 23:57:18 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgba
{
	double	r;
	double	g;
	double	b;
	double	a;
}	t_rgba;

t_rgba	ft_make_rgba(double r, double g, double b, double a);
t_rgba	ft_mul_rgba(t_rgba c, double t);
t_rgba	ft_add_rgba(t_rgba c1, t_rgba c2);
t_rgba	ft_sub_rgba(t_rgba c1, t_rgba c2);
t_rgba	ft_lerp_rgba(t_rgba c1, t_rgba c2, double t);
t_rgba	ft_clamp_rgba(t_rgba c);
t_rgba	ft_mul_rgba_rgba(t_rgba a, t_rgba b);
int		ft_get_color(t_rgba c);
t_rgba	ft_parse_rgba(char *line);
t_rgba	ft_blend_rgba(t_rgba c1, t_rgba c2);
double	ft_intensity_rgba(t_rgba c);

#endif
