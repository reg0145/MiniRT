/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:42:38 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 21:38:27 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../mlx/mlx.h"
#include <math.h>

static void	pixel_put(t_info *info, int x, int y, t_pt cl)
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

static int	is_shadow(t_info *info, t_hit_check *hit, t_ray ray, double len)
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
static t_pt	check_light(t_info *info, t_ray ray, t_hit_check hit)
{
	t_pong	pong;
	t_pt	color;
	t_ray	to_light;

	pong.lig_len = vlength(vsub(info->light.pos, hit.pos));	//광원과 광선과의 거리
	to_light = (t_ray){vadd(hit.pos, vmult(hit.n_vec, 1e-6)), \
		vunit(vsub(info->light.pos, hit.pos))};	//광원에서 광선의 방향
	if (is_shadow(info, &hit, to_light, pong.lig_len))	//그림자 확인
		return ((t_pt){0, 0, 0});
	pong.lig_dir = vunit(vsub(info->light.pos, hit.pos)); //광원에서 타점까지 방향
	pong.kd = fmax(vdot(hit.n_vec, pong.lig_dir), 0.0); // 라이팅 계산. 난반사를 구현하기 위해 cos 값을 사용한다. (cos값은 90도 이상에서 음수가 되는데 이를 0으로 만들어줌)
	pong.dif = vmult(info->light.color, pong.kd * info->light.ratio); // 난반사 적용
	pong.view_dir = vunit(vmult(ray.dir, -1));	//보이는 방향(카메라 방향)
	pong.ref_dir = vreflect(vmult(pong.lig_dir, -1), hit.n_vec);	//반사된 광선
	pong.spec = pow(fmax(vdot(pong.view_dir, pong.ref_dir), 0.0), KSN);	//반사된 광선과 보이는 방향의 내적. 90도면 0이 될것...!
	pong.specular = vmult((vmult(info->light.color, KS * \
		info->light.ratio)), pong.spec);
	color = vadd(vadd(pong.dif, pong.specular), \
		vmult(info->amb.color, info->amb.ratio)); // 광택 + 난반사 적용
	color = vmin(vmult_vec(color, hit.albedo), (t_pt){1, 1, 1}); // albedo 적용
	return (color); 
}

static t_pt	trace_ray(t_info *info, t_ray ray)
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

	i = -1;
	cam_init(info);
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			ray = ray_init(info, (double)i / (WIDTH - 1), \
					(double)j / (HEIGHT - 1));
			color = trace_ray(info, ray);
			pixel_put(info, i, HEIGHT - j - 1, color);
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}
