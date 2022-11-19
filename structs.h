#ifndef STRUCTS_H
# define STRUCTS_H

# include "./libft/headers/libft.h"

typedef enum e_obj
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef enum e_info_type
{
	AMB	= 0x0001,
	CAM	= 0x0002,
	LIGHT	= 0x0004,
}	t_info_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_pt
{
	double	x;
	double	y;
	double	z;
}	t_pt;

typedef struct s_ambient
{
	struct s_color	color;
	double			ratio;
}	t_ambient;

typedef struct s_cam
{
	struct s_pt	pos;
	struct s_pt	n_vec;
	double		fov;
}	t_cam;

typedef struct s_light
{
	struct s_pt	pos;
	double		ratio;
	// struct s_color	color;
}	t_light;

typedef struct s_sp
{
	struct s_pt		pos;
	struct s_color	color;
	double			r;
}	t_sp;

typedef struct s_pl
{
	struct s_pt		pos;
	struct s_pt		n_vec;
	struct s_color	color;
}	t_pl;

typedef struct s_cy
{
	struct s_pt		pos;
	struct s_pt		n_vec;
	struct s_color	color;
	double			r;
	double			height;
}	t_cy;

typedef struct s_obj
{
	int				type;
	void			*obj;
}	t_obj;

typedef struct s_info
{
	struct s_ambient	amb;
	struct s_cam		cam;
	struct s_light		light;
	t_list				*objs;
}	t_info;

#endif
