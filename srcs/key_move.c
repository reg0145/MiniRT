/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:27:05 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 00:12:58 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minirt.h"
#include "key_code.h"


static t_pt	cam_set_vup(t_pt dir)
{
	if (dir.x == 0 && dir.y != 0 && dir.z == 0)
		return ((t_pt){0, dir.y, 1e-6});
	else
		return ((t_pt){0, 1, 0});
}

void	move_camera(t_cam *cam, int keycode)
{
	t_pt	dir;
	t_pt	back;
	t_pt	right;
	t_pt	up;

	dir = cam->dir;
	back = vmult(dir, -1);
	right = vunit(vcross(cam_set_vup(dir), back));
	up = vunit(vcross(back, right));
	if (keycode == KEY_W)
		move_obj(&cam->pos, vmult(dir, MOVEMENT));
	if (keycode == KEY_S)
		move_obj(&cam->pos, vmult(dir, -MOVEMENT));
	if (keycode == KEY_A)
		move_obj(&cam->pos, vmult(right, -MOVEMENT));
	if (keycode == KEY_D)
		move_obj(&cam->pos, vmult(right, MOVEMENT));
	if (keycode == KEY_Q)
		move_obj(&cam->pos, vmult(up, -MOVEMENT));
	if (keycode == KEY_E)
		move_obj(&cam->pos, vmult(up, MOVEMENT));
}

void	move_light(t_light *light, t_pt dir, int keycode)
{
	t_pt	back;
	t_pt	right;
	t_pt	up;

	back = vmult(dir, -1);
	right = vunit(vcross(cam_set_vup(dir), back));
	up = vunit(vcross(back, right));
	if (keycode == KEY_W)
		move_obj(&light->pos, vmult(dir, MOVEMENT));
	if (keycode == KEY_S)
		move_obj(&light->pos, vmult(dir, -MOVEMENT));
	if (keycode == KEY_A)
		move_obj(&light->pos, vmult(right, -MOVEMENT));
	if (keycode == KEY_D)
		move_obj(&light->pos, vmult(right, MOVEMENT));
	if (keycode == KEY_Q)
		move_obj(&light->pos, vmult(up, -MOVEMENT));
	if (keycode == KEY_E)
		move_obj(&light->pos, vmult(up, MOVEMENT));
}

void	move_sphere(t_sp *sphere, t_pt dir, int keycode)
{
	t_pt	back;
	t_pt	right;
	t_pt	up;

	back = vmult(dir, -1);
	right = vunit(vcross(cam_set_vup(dir), back));
	up = vunit(vcross(back, right));
	if (keycode == KEY_W)
		move_obj(&sphere->pos, vmult(dir, MOVEMENT));
	if (keycode == KEY_S)
		move_obj(&sphere->pos, vmult(dir, -MOVEMENT));
	if (keycode == KEY_A)
		move_obj(&sphere->pos, vmult(right, -MOVEMENT));
	if (keycode == KEY_D)
		move_obj(&sphere->pos, vmult(right, MOVEMENT));
	if (keycode == KEY_Q)
		move_obj(&sphere->pos, vmult(up, -MOVEMENT));
	if (keycode == KEY_E)
		move_obj(&sphere->pos, vmult(up, MOVEMENT));
}

void	move_plane(t_pl *plane, t_pt dir, int keycode)
{
	t_pt	back;
	t_pt	right;
	t_pt	up;

	back = vmult(dir, -1);
	right = vunit(vcross(cam_set_vup(dir), back));
	up = vunit(vcross(back, right));
	if (keycode == KEY_W)
		move_obj(&plane->pos, vmult(dir, MOVEMENT));
	if (keycode == KEY_S)
		move_obj(&plane->pos, vmult(dir, -MOVEMENT));
	if (keycode == KEY_A)
		move_obj(&plane->pos, vmult(right, -MOVEMENT));
	if (keycode == KEY_D)
		move_obj(&plane->pos, vmult(right, MOVEMENT));
	if (keycode == KEY_Q)
		move_obj(&plane->pos, vmult(up, -MOVEMENT));
	if (keycode == KEY_E)
		move_obj(&plane->pos, vmult(up, MOVEMENT));
}

void	move_cylinder(t_cy *cylinder, t_pt dir, int keycode)
{
	t_pt	back;
	t_pt	right;
	t_pt	up;

	back = vmult(dir, -1);
	right = vunit(vcross(cam_set_vup(dir), back));
	up = vunit(vcross(back, right));
	if (keycode == KEY_W)
		move_obj(&cylinder->pos, vmult(dir, MOVEMENT));
	if (keycode == KEY_S)
		move_obj(&cylinder->pos, vmult(dir, -MOVEMENT));
	if (keycode == KEY_A)
		move_obj(&cylinder->pos, vmult(right, -MOVEMENT));
	if (keycode == KEY_D)
		move_obj(&cylinder->pos, vmult(right, MOVEMENT));
	if (keycode == KEY_Q)
		move_obj(&cylinder->pos, vmult(up, -MOVEMENT));
	if (keycode == KEY_E)
		move_obj(&cylinder->pos, vmult(up, MOVEMENT));
}
