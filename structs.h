#ifndef STRUCTS_H
# define STRUCTS_H

# include "./libft/headers/libft.h"
# include "./mlx/mlx.h"
#include <stddef.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

# define WIDTH 1200
# define HEIGHT 900

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

typedef struct s_pt
{
	double	x;
	double	y;
	double	z;
}	t_pt;

typedef struct s_ambient
{
	struct s_pt		color;
	double			ratio;
}	t_ambient;

typedef struct s_cam
{
	struct s_pt	pos;
	struct s_pt	dir;
	double		focal_len;
	double		v_h; // 뷰포트 세로길이
	double		v_w; // 뷰포트 가로길이
	struct s_pt	vp_ll; // 뷰포트 왼쪽 아래 꼭지점
	struct s_pt	hor; // 뷰포트 가로 방향 벡터
	struct s_pt	ver; // 뷰포트 세로 방향 벡터
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
	struct s_pt		color;
	double			r;
}	t_sp;

typedef struct s_pl
{
	struct s_pt		pos;
	struct s_pt		dir;
	struct s_pt		color;
}	t_pl;

typedef struct s_cy
{
	struct s_pt		pos;
	struct s_pt		dir;
	struct s_pt		color;
	double			r;
	double			height;
}	t_cy;

/* t_list의 content 안에 들어갈 정보. content를 t_obj로 형변환해서 사용 */
typedef struct s_obj
{
	int				type;
	void			*obj_info;
}	t_obj;

/* object에 광선이 맞았는지 아닌지 체크하기 위한 정보 */
typedef struct s_hit_check
{
	t_pt		pos;
	t_pt		dir;
	double		t;
	double		t_min;
	double		t_max;
	int			front_face;
	t_pt		albedo;
}	t_hit_check;

/* 추적할 광선에 대한 정보 */
typedef struct s_ray
{
	t_pt		pos;
	t_pt		dir;
}	t_ray;

typedef struct s_info
{
	/* mlx 관련 정보 */
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
	/* 오브젝트 관련 정보 */
	struct s_ambient	amb;
	struct s_cam		cam;
	struct s_light		light;
	t_list				*objs;
}	t_info;

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
void	exceve(t_info *info);

#endif
