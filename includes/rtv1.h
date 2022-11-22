/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:03:40 by ctrouve           #+#    #+#             */
/*   Updated: 2022/11/22 16:01:03 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "color.h"
# include "vector.h"
# include "keys.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define SCREEN_WIDTH 840
# define SCREEN_HEIGHT 620
# define MAX_DISTANCE 200
# define MIN_DISTANCE 0.1
# define SHADOW_ACNE 0.001
# define RAYS_PER_PIXEL	1
# define TRUE 1
# define FALSE 0

/*
** shadow "acne": https://www.scratchapixel.com/lessons/3d-basic-rendering/
** introduction-to-shading/ligth-and-shadows
** Because of some small numerical errors introduced by the fact that numbers 
** in our 3D engine can only be represented with a certain precision, sometimes,
** the intersection point is not exactly directly above the surface, but slightly
** below. To fix this we systematically displace the origin of the shadow ray in 
** the direction of the surface normal, to move it with above the surface:
** see function is_in_shadow() in light.c
*/

typedef struct s_color_data
{
	t_rgba		out;
	t_rgba		ambient;
	t_rgba		diffuse;
	t_rgba		specular;
	double		attenuation;
}				t_color_data;

typedef enum e_lgt_type
{
	DIRECTIONAL,
	POINT
}				t_lgt_type;

typedef struct s_light
{
	t_lgt_type	type;
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		direction;
	double		intensity;
	t_rgba		color;
}				t_light;

typedef enum e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	LIGHT,
	CAMERA
}				t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		scale;
	t_rgba		color;
	double		radius;
	t_vec3		start;
	t_vec3		end;
	t_vec3		normal;
}				t_object;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
	t_object	*origin_object;
	int			shad;
}				t_ray;

typedef struct s_quadratic
{
	double		a;
	double		b;
	double		c;
}				t_quadratic;

/* hit = point we investigate, t is solution to p=o+t*d
** in sole_quadratic det = b*b - 4.*a*c
** t = (-b - det) / (2. * a);
** t2 = (-b + det) / (2. * a)
*/
typedef struct s_hit
{
	t_vec3		point;
	t_vec3		normal;
	t_object	*object;
	t_vec3		light_dir;
	double		t;
	double		t2;
	double		distance;
	t_rgba		color;
}				t_hit;

/*
** see https://raytracing.github.io/books/
** RayTracingInOneWeekend.html#positionablecamera/cameraviewinggeometry
*/
typedef struct s_camera_info
{
	t_vec3		v_up;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
	double		theta;
	double		half_height;
	double		half_width;
}				t_camera_info;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		dir;
	double		fov;
	double		scale;
	double		aspect;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left_corner;
}				t_camera;

typedef struct s_scene
{
	char		*path;
	int			fd;
	t_object	*objects;
	t_light		*lights;
	int			num_lights;
	int			num_objects;
	t_rgba		ambient_color;
	t_camera	camera;
	t_object	*selected_object;
	t_light		*selected_light;
	int			l_index;
	int			o_index;
	int			a_color_read;
}				t_scene;

typedef struct s_mlx_img
{
	void		*img;
	char		*d_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_mlx_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct s_env
{
	t_mlx		*mlx;
	t_mlx_img	*mlx_img;
	t_scene		*scene;
	int			width;
	int			height;
}				t_env;

/* camera */

int			update_camera(t_camera *cam, t_vec3 pos, t_vec3 dir, double fov);
t_ray		get_camera_ray(t_camera *camera, double u, double v);
void		handle_camera_movement(t_env *env, int key);
t_vec2i		world_to_screen_point(t_camera *camera, t_vec3 wp);

/* draw_line */

void		draw_line(t_mlx *mlx, t_vec3 p0, t_vec3 p1, int color);

/* env */

t_env		*init_env(int width, int height, char *title);
void		del_env_exit(t_env *env);
int			close_window(void *param);
int			update(void *param);

/* image */

t_mlx_img	*create_mlx_image(t_env *env, int width, int height);
void		put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);
void		error_msg(char *message);

/* key_press & key_press_utils */

int			key_press(int key, void *param);
void		select_object_or_light(int key, t_env *env);

/* light */

void		init_light(t_light *light);
void		rotate_light(t_light *light, t_vec3 rot);
int			is_in_shadow(t_light *light, t_scene *scene, t_hit *origin);
t_rgba		calc_diffuse(t_light *light, t_hit *hit);
t_rgba		calc_specular(t_light *light, t_hit *hit, t_vec3 cam);

/* object */

void		init_object(t_object *object);
int			intersects_object(t_ray *ray, t_object *object, t_hit *hit);
int			solve_quadratic(t_quadratic q, double *t1, double *t2);
double		ft_deg_to_rad(double deg);
void		init_color_data(t_color_data *color, t_scene *scene, t_hit *hit);

/* obj_<object> */

void		rotate_cylinder(t_object *c, t_vec3 rot);
void		rotate_cone(t_object *c, t_vec3 rot);
void		rotate_plane(t_object *p, t_vec3 rot);
int			intersects_cylinder(t_ray *ray, t_object *sphere, t_hit *hit);
int			intersects_cone(t_ray *ray, t_object *cone, t_hit *hit);
int			intersects_plane(t_ray *ray, t_object *plane, t_hit *hit);
int			intersects_sphere(t_ray *ray, t_object *sphere, t_hit *hit);

/* parse */

int			parse_camera(int fd, t_camera *camera);
int			parse_light(int fd, t_light *light);
int			parse_object(int fd, t_obj_type type, t_object *object);

/* parse_utils */

t_vec3		ft_parsing_vec3(char *str);
t_rgba		ft_parsing_rgba(char *line);
int			check_dash(char *path);

/* ray */

t_vec3		point_on_ray(t_ray *r, double t);
void		init_raycasthit(t_hit *hit);
int			trace(t_ray *ray, t_scene *scene, t_hit *hit, int stop_at_first);
t_rgba		raycast(t_ray *ray, t_scene *scene, t_hit *hit);

/* rtv1 including main */

void		render(t_env *env, t_scene *scene);

/* scene */

int			read_scene(t_scene *scene, char *path);

#endif
