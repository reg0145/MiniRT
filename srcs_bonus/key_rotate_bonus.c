/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:21:02 by nheo              #+#    #+#             */
/*   Updated: 2022/11/29 11:55:44 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "key_code_bonus.h"
#include <math.h>

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
	if (keycode == KEY_Z)
		rotate_obj(&plane->dir, (t_pt){0, 0, ROTATION});
	if (keycode == KEY_X)
		rotate_obj(&plane->dir, (t_pt){0, 0, -ROTATION});
	if (keycode == KEY_UP)
		rotate_obj(&plane->dir, (t_pt){-ROTATION, 0, 0});
	if (keycode == KEY_DOWN)
		rotate_obj(&plane->dir, (t_pt){ROTATION, 0, 0});
	if (keycode == KEY_LEFT)
		rotate_obj(&plane->dir, (t_pt){0, -ROTATION, 0});
	if (keycode == KEY_RIGHT)
		rotate_obj(&plane->dir, (t_pt){0, ROTATION, 0});
}

void	rotate_cylinder(t_cy *cylinder, int keycode)
{
	if (keycode == KEY_Z)
		rotate_obj(&cylinder->dir, (t_pt){0, 0, ROTATION});
	if (keycode == KEY_X)
		rotate_obj(&cylinder->dir, (t_pt){0, 0, -ROTATION});
	if (keycode == KEY_UP)
		rotate_obj(&cylinder->dir, (t_pt){-ROTATION, 0, 0});
	if (keycode == KEY_DOWN)
		rotate_obj(&cylinder->dir, (t_pt){ROTATION, 0, 0});
	if (keycode == KEY_LEFT)
		rotate_obj(&cylinder->dir, (t_pt){0, ROTATION, 0});
	if (keycode == KEY_RIGHT)
		rotate_obj(&cylinder->dir, (t_pt){0, -ROTATION, 0});
}
