/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:57:47 by nheo              #+#    #+#             */
/*   Updated: 2022/11/23 14:07:13 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code.h"
#include "minirt.h"
#include <math.h>

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

int	is_rotate_key(int keycode)
{
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT || \
		keycode == KEY_UP || keycode == KEY_DOWN || \
		keycode == KEY_Z || keycode == KEY_X)
		return (TRUE);
	return (FALSE);
}

/* 물체 회전 */
void	key_rotate(void *clicked, int type, int keycode)
{
	if (type == PLANE)
		rotate_plane((t_pl *)((t_obj *)clicked)->obj_info, keycode);
	if (type == CYLINDER)
		rotate_cylinder((t_cy *)((t_obj *)clicked)->obj_info, keycode);
	if (type == CAMERA)
		rotate_camera((t_cam *)clicked, keycode);
}
