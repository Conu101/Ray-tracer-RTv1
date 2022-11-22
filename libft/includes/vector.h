/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:17:26 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/11 23:58:08 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef union u_vec3
{
	double		x;
	double		y;
	double		z;
	double		v[3];
}				t_uvec3;

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

t_vec3			ft_make_vec3(double x, double y, double z);
void			ft_set_vec3(t_vec3 *v, double x, double y, double z);
t_vec3			ft_add_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_sub_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_mul_vec3(t_vec3 v, double t);
t_vec3			ft_mul_vec3_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_div_vec3(t_vec3 v, double t);
double			ft_len_vec3(t_vec3 v1);
double			ft_dot_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_normalize_vec3(t_vec3 v);
t_vec3			ft_invert_vec3(t_vec3 v);
t_vec3			ft_reflect_vec3(t_vec3 v, t_vec3 n);
t_vec3			ft_cross_vec3(t_vec3 a, t_vec3 b);
t_vec3			ft_rotate_vec3(t_vec3 v, t_vec3 rot);
t_vec3			ft_parse_vec3(char *str);

#endif
