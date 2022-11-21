#include "structs.h"
#include <math.h>
#include <stdio.h>

double	root_formula(double a, double b, double c, t_hit_check *hit)
{
	double	discriminant;
	double	root1;
	double	root2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	root1 = (-b + sqrt(discriminant)) / (2 * a);
	root2 = (-b - sqrt(discriminant)) / (2 * a);
	if ((root1 < hit->t_min && root2 < hit->t_min) || \
		(root1 > hit->t_max && root2 > hit->t_max))
		return (-1);
	hit->is_surface = FALSE;
	if (discriminant <= 0.03)	// 0.03보다 작으면 표면으로 간주
		hit->is_surface = TRUE;
	if (fmin(root1, root2) > 0)
		return (fmin(root1, root2));
	return (fmax(root1, root2));
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
	a = vlength2(ray.dir);	//광선의 방향 벡터의 길이의 제곱
	b = 2 * vdot(oc, ray.dir); //광선의 방향 벡터와 oc의 내적 * 2
	c = vlength2(oc) - sp->r * sp->r; //oc의 길이의 제곱 - 구의 반지름의 제곱
	tmp = root_formula(a, b, c, hit); // t값 최대, 최소 범위 내에서의 광선과 구의 교점(근의 공식)
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	hit->t = tmp;
	hit->albedo = sp->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = vdiv(vsub(hit->pos, sp->pos), sp->r);
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

int	hit_plane(t_pl *pl, t_ray ray, t_hit_check *hit)
{
	double	denom;	//직선의 방정식 분모
	double	numer;	//직선의 방정식 분자
	double	tmp;

	denom = vdot(pl->dir, ray.dir);	//평면의 방향 벡터와 광선의 방향 벡터의 내적 (기울기)
	if (fabs(denom) < 1e-6)
		return (FALSE);
	numer = vdot(vsub(pl->pos, ray.pos), pl->dir); //평면의 방향 벡터와 광선의 시작점과 평면의 거리의 내적
	tmp = numer / denom;	//t값
	if (tmp < hit->t_min || hit->t_max <= tmp)
		return (FALSE);
	hit->t = tmp;
	hit->albedo = pl->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = pl->dir;
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
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
	t_hit_check	tmp;
	t_list		*list;
	int			return_value;

	return_value = FALSE;
	list = info->objs;
	tmp = *hit;
	while (list)
	{
		obj = (t_obj *)list->content;
		if (hit_check(obj, ray, &tmp))
		{
			if (tmp.t_max > tmp.t)
			{
				tmp.t_max = tmp.t;
				return_value = TRUE;
				*hit = tmp;
			}
		}
		list = list->next;
	}
	return (return_value);
}

int	is_shadow(t_info *info, t_hit_check *hit, t_ray ray, double len)
{
	hit->t_min = 0;
	hit->t_max = len;
	if (check_objs(info, ray, hit))
		return (TRUE);
	return (FALSE);
}
/* 
	퐁 모델 적용하는 함수. 퐁 모델은 diffuse(난반사) + specular(정반사) + ambient(주변광) + emissive light(여기서는 사용 x)로 적용된다
*/
t_pt	check_light(t_info *info, t_ray ray, t_hit_check hit)
{
	t_pong	pong;
	t_pt	color;
	t_ray	to_light;

	pong.len = vlength(vsub(info->light.pos, hit.pos));	//광원과 광선과의 거리
	to_light = (t_ray){vadd(hit.pos, vmult(hit.n_vec, 1e-6)), \
		vunit(vsub(info->light.pos, hit.pos))};	//광원에서 광선의 방향
	if (is_shadow(info, &hit, to_light, pong.len))	//그림자 확인
		return ((t_pt){0, 0, 0});
	pong.lig_dir = vunit(vsub(info->light.pos, hit.pos)); //광원에서 타점까지 방향
	pong.kd = fmax(vdot(hit.n_vec, pong.lig_dir), 0.0); // 라이팅 계산. 난반사를 구현하기 위해 cos 값을 사용한다. (cos값은 90도 이상에서 음수가 되는데 이를 0으로 만들어줌)
	pong.dif = vmult(info->light.color, pong.kd * info->light.ratio); // 난반사 적용
	pong.view_dir = vunit(vmult(ray.dir, -1));	//보이는 방향(카메라 방향)
	pong.ref_dir = vreflect(vmult(pong.lig_dir, -1), hit.n_vec);	//반사된 광선
	pong.ksn = 50; //광택 계수 (매끄러울수록 높음, 높을수록 하이라이팅 범위가 줄어듬)
	pong.ks = 1;	//광택 정도
	pong.spec = pow(fmax(vdot(pong.view_dir, pong.ref_dir), 0.0), pong.ksn);	//반사된 광선과 보이는 방향의 내적. 90도면 0이 될것...!
	pong.specular = vmult((vmult(info->light.color, pong.ks * \
		info->light.ratio)), pong.spec);
	color = vadd(vadd(pong.dif, pong.specular), \
		vmult(info->amb.color, info->amb.ratio)); // 광택 + 난반사 적용
	if (pong.spec)
		(void)color;
	color = vmin(vmult_vec(color, hit.albedo), (t_pt){1, 1, 1}); // albedo 적용
	if (hit.is_surface)
		// color = vadd(vmult(color, 0.5), vmult(info->light.color, 0.5)); //표면인 경우 반사체면 반사도를 반으로 줄임...(경계면 표현, object와 object 사이에는 적용 못함ㅠㅠ)
		color = vmult(color, 0.5); //표면인 경우 반사체면 반사도를 반으로 줄임... (경계면 표현, object와 object 사이에는 적용 못함ㅠㅠ)
	return (color); 
}

t_pt	trace_ray(t_info *info, t_ray ray)
{
	t_hit_check	hit;

	ft_memset(&hit, 0, sizeof(t_hit_check));
	hit.t_max = 10000;
	hit.t_min = 1e-6;
	hit.t = hit.t_max;
	if (check_objs(info, ray, &hit))
		return (check_light(info, ray, hit));
	// return ((info->light.color));	//배경 : 빛 색
	return ((t_pt){0, 0, 0});		//배경 : 검은색
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
