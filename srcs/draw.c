/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:42:38 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 21:38:41 by nheo             ###   ########.fr       */
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

static t_pt	check_light(t_info *info, t_ray ray, t_hit_check hit)
{
	t_pong	pong;
	t_pt	color;
	t_ray	to_light;

	pong.lig_len = vlength(vsub(info->light.pos, hit.pos));
	to_light = (t_ray){vadd(hit.pos, vmult(hit.n_vec, 1e-6)), \
		vunit(vsub(info->light.pos, hit.pos))};
	if (is_shadow(info, &hit, to_light, pong.lig_len))
		return ((t_pt){0, 0, 0});
	pong.lig_dir = vunit(vsub(info->light.pos, hit.pos));
	pong.kd = fmax(vdot(hit.n_vec, pong.lig_dir), 0.0);
	pong.dif = vmult(info->light.color, pong.kd * info->light.ratio);
	pong.view_dir = vunit(vmult(ray.dir, -1));
	pong.ref_dir = vreflect(vmult(pong.lig_dir, -1), hit.n_vec);
	pong.spec = pow(fmax(vdot(pong.view_dir, pong.ref_dir), 0.0), KSN);
	pong.specular = vmult((vmult(info->light.color, KS * \
		info->light.ratio)), pong.spec);
	color = vadd(vadd(pong.dif, pong.specular), \
		vmult(info->amb.color, info->amb.ratio));
	color = vmin(vmult_vec(color, hit.albedo), (t_pt){1, 1, 1});
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
	return ((t_pt){0, 0, 0});
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
