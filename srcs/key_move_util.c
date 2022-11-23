/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:23:35 by nheo              #+#    #+#             */
/*   Updated: 2022/11/23 14:23:36 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code.h"
#include "minirt.h"

/* 물체 이동 (카메라가 보는 방향 기준에서 이동) */
void	key_move(void *clicked, int type, t_pt dir, int keycode)
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

int	is_move_key(int keykode)
{
	if (keykode == KEY_W || keykode == KEY_S || keykode == KEY_A || \
		keykode == KEY_D || keykode == KEY_Q || keykode == KEY_E)
		return (TRUE);
	return (FALSE);
}

void	move_obj(t_pt *pos, t_pt dir)
{
	*pos = vadd(*pos, dir);
}
