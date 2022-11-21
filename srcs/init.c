/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:43:49 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 00:54:18 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../mlx/mlx.h"
#include <math.h>

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

void	mlx_info_init(t_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "miniRT");
	info->img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->addr = mlx_get_data_addr(info->img, &info->bpp, \
		&info->size_line, &info->endian);
}
