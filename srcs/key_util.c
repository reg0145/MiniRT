/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:47:35 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 00:54:48 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "key_code.h"

/* 물체 이동 (카메라가 보는 방향 기준에서 이동) */
static void	key_move(void *clicked, int type, t_pt dir, int keycode)
{
	if (type == PLANE)
		move_plane((t_pl *)((t_obj *)clicked)->obj_info, dir, keycode);
	if (type == SPHERE)
		move_sphere((t_sp *)((t_obj *)clicked)->obj_info, dir, keycode);
	if (type == CYLINDER)
		move_cylinder((t_cy *)((t_obj *)clicked)->obj_info, dir, keycode);
	if (type == LIGHT)
		move_light((t_light *)clicked, dir, keycode);
	if (type == CAMERA)
		move_camera((t_cam *)clicked, keycode);
}

/* 물체 회전 */
static void	key_rotate(void *clicked, int type, int keycode)
{
	if (type == PLANE)
		rotate_plane((t_pl *)((t_obj *)clicked)->obj_info, keycode);
	if (type == CYLINDER)
		rotate_cylinder((t_cy *)((t_obj *)clicked)->obj_info, keycode);
	if (type == CAMERA)
		rotate_camera((t_cam *)clicked, keycode);
}

int	is_rotate_key(int keycode)
{
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT || \
		keycode == KEY_UP || keycode == KEY_DOWN || \
		keycode == KEY_Z || keycode == KEY_X)
		return (TRUE);
	return (FALSE);
}

int	is_valid_key(int keycode)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || \
		keycode == KEY_D || keycode == KEY_LEFT || keycode == KEY_RIGHT || \
		keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_ESC || \
		keycode == KEY_L || keycode == KEY_C || keycode == KEY_Q || \
		keycode == KEY_E || keycode == KEY_Z || keycode == KEY_X)
		return (TRUE);
	return (FALSE);
}

int	key_press(int keycode, t_info *info)
{
	if (!is_valid_key(keycode))
		return (0);
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_L)
	{
		info->clicked_type = LIGHT;
		info->clicked = &info->light;
	}
	if (keycode == KEY_C)
	{
		info->clicked_type = CAMERA;
		info->clicked = &info->cam;
	}
	if (keycode == KEY_DELETE)
		info->clicked = NULL;
	if (!info->clicked)
		return (0);
	if (is_rotate_key(keycode))
		key_rotate(info->clicked, info->clicked_type, keycode);
	else
		key_move(info->clicked, info->clicked_type, info->cam.dir, keycode);
	draw(info);
	return (0);
}
