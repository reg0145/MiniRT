/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:40:54 by nheo              #+#    #+#             */
/*   Updated: 2022/11/28 16:36:53 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"

# define WIDTH 720
# define HEIGHT 600
# define TRUE 1
# define FALSE 0

# define KSN 32
# define KS 1

# define MOVEMENT 0.1
# define ROTATION 0.1
# define RESIZE 0.1
typedef enum e_obj
{
	SPHERE,
	PLANE,
	CYLINDER,
	CAMERA,
	LIGHT
}	t_object_type;

typedef enum e_info_type
{
	AMB	= 0x0001,
	CAM	= 0x0002,
	LIT	= 0x0004,
}	t_info_type;

/* vectors */
double	vlength2(t_pt vec);
double	vlength(t_pt vec);
t_pt	vunit(t_pt vec);
t_pt	vadd(t_pt vec1, t_pt vec2);
t_pt	vsub(t_pt vec1, t_pt vec2);
t_pt	vmult(t_pt vec, double num);
t_pt	vmult_vec(t_pt vec1, t_pt vec2);
t_pt	vdiv(t_pt vec, double t);
double	vdot(t_pt vec1, t_pt vec2);
t_pt	vcross(t_pt vec1, t_pt vec2);
t_pt	vreflect(t_pt vec, t_pt n_vec);
t_pt	vmin(t_pt vec1, t_pt vec2);

/* parse with ',' */
t_pt	parse_color(char *str);
t_pt	parse_pt(char *str);
t_pt	parse_n_vec(char *str);

void	mlx_info_init(t_info *info);
t_pt	cam_set_vup(t_pt dir);
void	cam_init(t_info *info);
t_ray	ray_init(t_info *info, double x, double y);

/* key press */
int		is_move_key(int keykode);
int		is_rotate_key(int keycode);
int		is_size_key(int keycode);
int		key_press(int keycode, t_info *info);
void	print_key_info(t_info *info);
void	key_move(void *clicked, int type, t_pt dir, int keycode);
void	key_rotate(void *clicked, int type, int keycode);
void	key_size(void *clicked, int type, int keycode);

/* move objects */
void	move_obj(t_pt *pos, t_pt dir);
void	move_camera(t_cam *cam, int keycode);
void	move_light(t_light *light, t_pt dir, int keycode);
void	move_sphere(t_sp *sphere, t_pt dir, int keycode);
void	move_plane(t_pl *plane, t_pt dir, int keycode);
void	move_cylinder(t_cy *cylinder, t_pt dir, int keycode);

/* rotate objects */
void	rotate_obj(t_pt *dir, t_pt rot);
void	rotate_camera(t_cam *cam, int keycode);
void	rotate_plane(t_pl *plane, int keycode);
void	rotate_cylinder(t_cy *cylinder, int keycode);

/* parse */
void	check_file_extension(char *file);
void	read_file(char *file, char **content);
void	parse_to_info(char *content, t_info *info);
void	parse_ambient(char **args, t_info *info);
void	parse_camera(char **args, t_info *info);
void	parse_light(char **args, t_info *info);
void	parse_sphere(char **args, t_info *info);
void	parse_plane(char **args, t_info *info);
void	parse_cylinder(char **args, t_info *info);
void	check_n_vec(t_pt vec);

/* for check_hit */
int		check_objs(t_info *info, t_ray ray, t_hit_check *hit);
int		hit_check(t_obj *obj, t_ray ray, t_hit_check *hit);
int		hit_cylinder(t_cy *cy, t_ray ray, t_hit_check *hit);
int		hit_plane(t_pl *pl, t_ray ray, t_hit_check *hit);
int		hit_sphere(t_sp *sp, t_ray ray, t_hit_check *hit);
double	root_formula(double a, double b, double c, t_hit_check *hit);

void	draw(t_info *info);
int		mouse_click(int button, int x, int y, void *param);
void	reverse_color(t_obj *obj);

#endif
