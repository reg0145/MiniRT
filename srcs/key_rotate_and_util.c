/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate_and_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:21:02 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 01:44:37 by nheo             ###   ########.fr       */
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

	tmp = (t_pt){dir->x, dir->y, dir->z};
	if (rot.x)
	{
		dir->y = tmp.y * cos(rot.x) - tmp.z * sin(rot.x);
		dir->z = tmp.y * sin(rot.x) + tmp.z * cos(rot.x);
	}
	if (rot.y)
	{
		dir->x = tmp.x * cos(rot.y) - tmp.z * sin(rot.y);
		dir->z = tmp.x * sin(rot.y) + tmp.z * cos(rot.y);
	}
	if (rot.z)
	{
		dir->x = tmp.x * cos(rot.z) - tmp.y * sin(rot.z);
		dir->y = tmp.x * sin(rot.z) + tmp.y * cos(rot.z);
	}
	*dir = vunit(*dir);
}

void	rotate_camera(t_cam *cam, int keycode)
{
	if (keycode == KEY_Z)
		rotate_obj(&cam->dir, (t_pt){0, 0, ROTATION});
	if (keycode == KEY_X)
		rotate_obj(&cam->dir, (t_pt){0, 0, -ROTATION});
	if (keycode == KEY_UP)
		rotate_obj(&cam->dir, (t_pt){-ROTATION, 0, 0});
	if (keycode == KEY_DOWN)
		rotate_obj(&cam->dir, (t_pt){ROTATION, 0, 0});
	if (keycode == KEY_LEFT)
		rotate_obj(&cam->dir, (t_pt){0, -ROTATION, 0});
	if (keycode == KEY_RIGHT)
		rotate_obj(&cam->dir, (t_pt){0, ROTATION, 0});
}

void	rotate_plane(t_pl *plane, int keycode)
{
	if (keycode == KEY_LEFT)
		rotate_obj(&plane->dir, (t_pt){0, 0, ROTATION});
	if (keycode == KEY_RIGHT)
		rotate_obj(&plane->dir, (t_pt){0, 0, -ROTATION});
	if (keycode == KEY_UP)
		rotate_obj(&plane->dir, (t_pt){-ROTATION, 0, 0});
	if (keycode == KEY_DOWN)
		rotate_obj(&plane->dir, (t_pt){ROTATION, 0, 0});
	if (keycode == KEY_Z)
		rotate_obj(&plane->dir, (t_pt){0, -ROTATION, 0});
	if (keycode == KEY_X)
		rotate_obj(&plane->dir, (t_pt){0, ROTATION, 0});
}

void	rotate_cylinder(t_cy *cylinder, int keycode)
{
	if (keycode == KEY_UP)
		rotate_obj(&cylinder->dir, (t_pt){0, 0, ROTATION});
	if (keycode == KEY_DOWN)
		rotate_obj(&cylinder->dir, (t_pt){0, 0, -ROTATION});
	if (keycode == KEY_LEFT)
		rotate_obj(&cylinder->dir, (t_pt){-ROTATION, 0, 0});
	if (keycode == KEY_RIGHT)
		rotate_obj(&cylinder->dir, (t_pt){ROTATION, 0, 0});
	if (keycode == KEY_Z)
		rotate_obj(&cylinder->dir, (t_pt){0, ROTATION, 0});
	if (keycode == KEY_X)
		rotate_obj(&cylinder->dir, (t_pt){0, -ROTATION, 0});
}
