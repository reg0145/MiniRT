#include "structs.h"
#include <math.h>

void	pixel_put(t_info *info, int x, int y, t_color cl)
{
	char			*img_addr;
	unsigned int	color_hex;
	int				red;
	int				green;
	int				blue;

	red = (int)(cl.r * 255);
	green = (int)(cl.g * 255);
	blue = (int)(cl.b * 255);
	color_hex = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	y = HEIGHT - y;
	img_addr = &info->addr[(y * info->size_line + x * \
		(info->bpp / 8))];
	*(unsigned int *)img_addr = color_hex;
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == 53)
		exit(0);
	(void)info;
	return (0);
}

void	draw(t_info *info)
{
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_hook(info->win, 2, 0, key_press, info);
}

void	init_mlx_info(t_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "miniRT");
	info->img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->addr = mlx_get_data_addr(info->img, &info->bpp, \
		&info->size_line, &info->endian);
}

t_ray	ray_init(t_info *info, double x, double y)
{
	t_cam	cam;
	t_ray	ray;

	cam = info->cam;
	ray.pos = info->cam.pos;
	ray.dir = vunit(vsub(vadd(cam.vp_ll, vadd(vmult(cam.hor, x), \
		vmult(cam.ver, y))), cam.pos)); //광선의 방향 : 현 위치 - 카메라 벡터
	return (ray);
}

static t_pt	cam_set_vup(t_pt dir)
{
	if (dir.x == 0 && dir.y != 0 && dir.z == 0)
		return ((t_pt){0, dir.y, 1e-6});
	else
		return ((t_pt){0, 1, 0});
}

void	cam_init(t_info *info)
{
	t_pt	w;
	t_pt	u;
	t_pt	v;

	info->cam.dir = vunit(info->cam.dir);
	info->cam.focal_len = tan((info->cam.focal_len * M_PI / 180.0) / 2.0);	//cam과 화면 사이의 거리
	info->cam.v_h = 2.0 * info->cam.focal_len; // 뷰포트 세로길이
	info->cam.v_w = info->cam.v_h * (double)WIDTH / (double)HEIGHT; // 뷰포트 가로길이
	w = vunit(vmult(info->cam.dir, -1));  // 카메라 방향 벡터의 반대 방향
	u = vunit(vcross(cam_set_vup(info->cam.dir), w));  // 카메라 방향 벡터와 수직인 벡터
	v = vcross(w, u);  // 카메라 방향 벡터와 수직인 벡터
	info->cam.vp_ll = vsub(vsub(info->cam.pos, vdiv(u, info->cam.v_w / 2.0)), \
		vdiv(v, info->cam.v_h / 2.0)); // 뷰포트 왼쪽 아래 꼭지점
}

t_hit_check	hit_sphere(t_obj *sp, t_ray ray, t_hit_check hit)
{
	(void)hit;
	(void)ray;
	(void)sp;
	return (hit);
}

t_hit_check	hit_plane(t_obj *pl, t_ray ray, t_hit_check hit)
{
	(void)hit;
	(void)ray;
	(void)pl;
	return (hit);
}

t_hit_check	hit_cylinder(t_obj *cy, t_ray ray, t_hit_check hit)
{
	(void)hit;
	(void)ray;
	(void)cy;
	return (hit);
}

t_hit_check hit_check(t_obj *obj, t_ray ray)
{
	t_hit_check	hit;

	hit.t_max = INFINITY;
	hit.t_min = 1e-6;
	if (obj->type == SPHERE)
		hit = hit_sphere(obj, ray, hit);
	if (obj->type == PLANE)
		hit = hit_plane(obj, ray, hit);
	if (obj->type == CYLINDER)
		hit = hit_cylinder(obj, ray, hit);
	return (hit);
}

t_hit_check check_objs(t_info *info, t_ray ray)
{
	t_hit_check	hit;
	t_hit_check	tmp;
	t_obj		*obj;
	t_list		*list;

	list = info->objs;
	hit.t = INFINITY;
	while (list)
	{
		obj = (t_obj *)list->content;
		tmp = hit_check(obj, ray);
		if (tmp.t > 0 && tmp.t < hit.t)
			hit = tmp;
		list = list->next;
	}
	return (hit);
}

t_color check_light(t_info *info, t_ray ray, t_hit_check hit)
{
	(void)hit;
	(void)ray;
	(void)info;
	return ((t_color){125, 125, 130});
}

t_color	trace_ray(t_info *info, t_ray ray)
{
	t_hit_check	hit;
	t_color		color;

	hit = check_objs(info, ray);
	color = check_light(info, ray, hit);
	return (color);
}

void	exceve(t_info *info)
{
	int		i;
	int		j;
	t_ray	ray;
	t_color	color;

	init_mlx_info(info);
	i = 0;
	cam_init(info);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ray = ray_init(info, (double)j / (WIDTH - 1),
				(double)i / (HEIGHT - 1));
			color = trace_ray(info, ray);
			pixel_put(info, j, i, color);
			j++;
		}
		i++;
	}
	draw(info);
	mlx_loop(info->mlx);
}
