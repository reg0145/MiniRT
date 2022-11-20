#include "structs.h"
#include <math.h>

double	root_formula(double a, double b, double c, t_hit_check hit)
{
	double	discriminant;
	double	root1;
	double	root2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	root1 = (-b + sqrt(discriminant)) / (2 * a);
	root2 = (-b - sqrt(discriminant)) / (2 * a);
	if ((root1 < hit.t_min && root2 < hit.t_min) || \
		(root1 > hit.t_max && root2 > hit.t_max))
		return (-1);
	return (fmin(root1, root2));
}

void	pixel_put(t_info *info, int x, int y, t_pt cl)
{
	char			*img_addr;
	unsigned int	color_hex;
	int				red;
	int				green;
	int				blue;

	red = (int)(cl.x * 255);
	green = (int)(cl.y * 255);
	blue = (int)(cl.z * 255);
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
	ray.dir = vunit(vsub(vadd(vadd(cam.vp_ll, vmult(cam.hor, x)), \
		vmult(cam.ver, y)), cam.pos)); //광선의 방향 : 현 위치 - 카메라 벡터
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
	info->cam.focal_len = tan((info->cam.fov * M_PI / 180.0) / 2.0);	//cam과 화면 사이의 거리
	info->cam.v_h = 2.0 * info->cam.focal_len; // 뷰포트 세로길이 (2.0은 임의의 상수값)
	info->cam.v_w = info->cam.v_h * (double)WIDTH / (double)HEIGHT; // 뷰포트 가로길이
	w = vunit(vmult(info->cam.dir, -1));  // 카메라 방향 벡터의 반대 방향
	u = vunit(vcross(cam_set_vup(info->cam.dir), w));  // 카메라 방향 벡터와 수직인 벡터 -> 오른쪽 방향 벡터
	v = vcross(w, u);  // 카메라 방향 벡터와 수직인 벡터
	info->cam.hor = vmult(u, info->cam.v_w); // 뷰포트 가로길이만큼 오른쪽으로 이동
	info->cam.ver = vmult(v, info->cam.v_h); // 뷰포트 세로길이만큼 위로 이동
	info->cam.vp_ll = vsub(vsub(vsub(info->cam.pos, \
		vdiv(info->cam.hor, 2)), vdiv(info->cam.ver, 2)), w); // 뷰포트 왼쪽 아래 꼭지점
}

int	hit_sphere(t_sp *sp, t_ray ray, t_hit_check *hit)
{
	t_pt	oc;
	double	a;
	double	b;
	double	c;
	double	tmp;

	oc = vsub(ray.pos, sp->pos); //광선의 시작점 - 구의 중심
	a = vlength2(ray.dir);	//광선의 방향
	b = 2 * vdot(oc, ray.dir); //광선의 시작점 - 구의 중심 * 광선의 방향
	c = vlength2(oc) - sp->r * sp->r; //광선의 시작점 - 구의 중심 * 광선의 시작점 - 구의 중심
	tmp = root_formula(a, b, c, *hit); // t값 최대, 최소 범위 내에서의 광선과 구의 교점
	if (tmp < hit->t_min || tmp > hit->t)
		return (FALSE);
	hit->t = tmp;
	hit->albedo = sp->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->dir = vdiv(vsub(hit->pos, sp->pos), sp->r);
	if (vdot(ray.dir, hit->dir) > 0)
		hit->dir = vmult(hit->dir, -1);
	return (TRUE);
}

int	hit_plane(t_pl *pl, t_ray ray, t_hit_check *hit)
{
	(void)hit;
	(void)ray;
	(void)pl;
	return (TRUE);
}

int	hit_cylinder(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	(void)hit;
	(void)ray;
	(void)cy;
	return (TRUE);
}

int	hit_check(t_obj *obj, t_ray ray, t_hit_check *hit)
{
	int	return_value;

	if (obj->type == SPHERE)
		return_value = hit_sphere((t_sp *)obj->obj_info, ray, hit);
	if (obj->type == PLANE)
		return_value = hit_plane((t_pl *)obj->obj_info, ray, hit);
	if (obj->type == CYLINDER)
		return_value = hit_cylinder((t_cy *)obj->obj_info, ray, hit);
	return (return_value);
}

int check_objs(t_info *info, t_ray ray, t_hit_check *hit)
{
	t_obj		*obj;
	t_list		*list;
	int			return_value;

	return_value = FALSE;
	list = info->objs;
	while (list)
	{
		obj = (t_obj *)list->content;
		if (hit_check(obj, ray, hit))
		{
			hit->t_max = hit->t;
			return_value = TRUE;
		}
		list = list->next;
	}
	return (return_value);
}

int	is_shadow(t_info *info, t_hit_check hit, t_ray ray, double len)
{
	t_hit_check	tmp;

	hit.t_min = 0;
	hit.t_max = len;
	if (check_objs(info, ray, &tmp))
		return (TRUE);
	return (FALSE);
}

t_pt	check_light(t_info *info, t_ray ray, t_hit_check hit)
{
	t_pong	pong;
	t_pt	color;

	pong.lig_dir = vunit(vsub(info->light.pos, hit.pos));
	pong.len = vlength(vsub(info->light.pos, hit.pos));
	if (is_shadow(info, hit, ray, pong.len))	//그림자 확인
		return ((t_pt){0, 0, 0});
	pong.kd = fmax(vdot(pong.lig_dir, hit.dir), 0);
	pong.dif = vmult(info->light.color, pong.kd * info->light.ratio);
	pong.view_dir = vunit(vmult(ray.dir, -1));	//보이는 방향(카메라 방향)
	pong.ref_dir = vreflect(vmult(pong.lig_dir, -1), hit.dir);	//반사된 광선
	pong.ksn = 511; //반사광 강도
	pong.ks = 1;	//광택 정도
	pong.spec = pow(fmax(vdot(pong.lig_dir, pong.ref_dir), 0), pong.ksn);	//반사된 광선과 보이는 방향의 내적. 90도면 0이 될것...!
	pong.specular = vmult((vmult(info->light.color, pong.ks * \
		info->light.ratio)), pong.spec);
	color = vadd(vadd(pong.dif, pong.specular), \
		vmult(info->amb.color, info->amb.ratio)); // 광택 + 난반사
	return (vsub(vmult_vec(hit.albedo, color), (t_pt){1,1,1}));
}

t_pt	check_color(t_info *info, t_ray ray, t_hit_check hit)
{
	(void)hit;
	(void)ray;
	(void)info;
	if (hit.t < 10000)
		return (check_light(info, ray, hit));
	return ((t_pt){0, 0, 0});
}

t_pt	trace_ray(t_info *info, t_ray ray)
{
	t_hit_check	hit;
	t_pt		color;

	ft_memset(&hit, 0, sizeof(t_hit_check));
	hit.t_max = 10000;
	hit.t_min = 1e-6;
	hit.t = hit.t_max;
	check_objs(info, ray, &hit);
	color = check_color(info, ray, hit);
	return (color);
}

void	draw(t_info *info)
{
	int		i;
	int		j;
	t_ray	ray;
	t_pt	color;

	init_mlx_info(info);
	i = -1;
	cam_init(info);
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			ray = ray_init(info, (double)i / (WIDTH - 1),
				(double)j / (HEIGHT - 1));
			color = trace_ray(info, ray);
			pixel_put(info, i, HEIGHT - j - 1, color);
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_hook(info->win, 2, 0, key_press, info);
}

void	exceve(t_info *info)
{
	draw(info);
	mlx_loop(info->mlx);
}
