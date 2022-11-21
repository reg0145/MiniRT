/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:43:49 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 02:42:55 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../mlx/mlx.h"
#include <math.h>

t_pt	cam_set_vup(t_pt dir)
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
	info->cam.focal_len = tan((info->cam.fov * M_PI / 180.0) / 2.0);
	info->cam.v_h = 2.0 * info->cam.focal_len;
	info->cam.v_w = info->cam.v_h * (double)WIDTH / (double)HEIGHT;
	w = vunit(vmult(info->cam.dir, -1));
	u = vunit(vcross(cam_set_vup(info->cam.dir), w));
	v = vcross(w, u);
	info->cam.hor = vmult(u, info->cam.v_w);
	info->cam.ver = vmult(v, info->cam.v_h);
	info->cam.vp_ll = vsub(vsub(vsub(info->cam.pos, \
		vdiv(info->cam.hor, 2)), vdiv(info->cam.ver, 2)), w);
}

t_ray	ray_init(t_info *info, double x, double y)
{
	t_cam	cam;
	t_ray	ray;

	cam = info->cam;
	ray.pos = info->cam.pos;
	ray.dir = vunit(vsub(vadd(vadd(cam.vp_ll, vmult(cam.hor, x)), \
		vmult(cam.ver, y)), cam.pos));
	return (ray);
}

void	mlx_info_init(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		ft_error("mlx_init() failed");
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "miniRT");
	if (!info->win)
		ft_error("mlx_new_window() failed");
	info->img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!info->img)
		ft_error("mlx_new_image() failed");
	info->addr = mlx_get_data_addr(info->img, &info->bpp, \
		&info->size_line, &info->endian);
	if (!info->addr)
		ft_error("mlx_get_data_addr() failed");
}
