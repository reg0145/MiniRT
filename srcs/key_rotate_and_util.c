/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate_and_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:21:02 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 17:42:50 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "key_code.h"
#include <math.h>

void	move_obj(t_pt *pos, t_pt dir)
{
	*pos = vadd(*pos, dir);
}

void	rotate_obj(t_pt *dir, t_pt rot)
{
	t_pt	tmp;

	tmp.x = dir->x;
	tmp.y = dir->y;
	tmp.z = dir->z;
	dir->x = tmp.x * cos(rot.x) + tmp.y * sin(rot.x);
	dir->y = tmp.y * cos(rot.y) + tmp.z * sin(rot.y);
	dir->z = tmp.z * cos(rot.z) + tmp.x * sin(rot.z);
}

void	rotate_camera(t_cam *cam, int keycode)
{
	if (keycode == KEY_UP)
		move_obj(&cam->dir, (t_pt){0, 0, 0.2});
	if (keycode == KEY_DOWN)
		move_obj(&cam->dir, (t_pt){0, 0, -0.2});
	if (keycode == KEY_LEFT)
		move_obj(&cam->dir, (t_pt){-0.2, 0, 0});
	if (keycode == KEY_RIGHT)
		move_obj(&cam->dir, (t_pt){0.2, 0, 0});
	if (keycode == KEY_Z)
		move_obj(&cam->dir, (t_pt){0, 0.2, 0});
	if (keycode == KEY_X)
		move_obj(&cam->dir, (t_pt){0, -0.2, 0});
}

void	rotate_plane(t_pl *plane, int keycode)
{
	if (keycode == KEY_UP)
		rotate_obj(&plane->dir, (t_pt){0, 0, 0.1});
	if (keycode == KEY_DOWN)
		rotate_obj(&plane->dir, (t_pt){0, 0, -0.1});
	if (keycode == KEY_LEFT)
		rotate_obj(&plane->dir, (t_pt){-0.1, 0, 0});
	if (keycode == KEY_RIGHT)
		rotate_obj(&plane->dir, (t_pt){0.1, 0, 0});
	if (keycode == KEY_Z)
		rotate_obj(&plane->dir, (t_pt){0, 0.1, 0});
	if (keycode == KEY_X)
		rotate_obj(&plane->dir, (t_pt){0, -0.1, 0});
}

void	rotate_cylinder(t_cy *cylinder, int keycode)
{
	if (keycode == KEY_UP)
		rotate_obj(&cylinder->dir, (t_pt){0, 0, 0.1});
	if (keycode == KEY_DOWN)
		rotate_obj(&cylinder->dir, (t_pt){0, 0, -0.1});
	if (keycode == KEY_LEFT)
		rotate_obj(&cylinder->dir, (t_pt){-0.1, 0, 0});
	if (keycode == KEY_RIGHT)
		rotate_obj(&cylinder->dir, (t_pt){0.1, 0, 0});
	if (keycode == KEY_Z)
		rotate_obj(&cylinder->dir, (t_pt){0, 0.1, 0});
	if (keycode == KEY_X)
		rotate_obj(&cylinder->dir, (t_pt){0, -0.1, 0});
}