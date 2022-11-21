/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:27:05 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 21:37:06 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minirt.h"
#include "key_code.h"

void	move_camera(t_cam *cam, int keycode)
{
	if (keycode == KEY_W)
		move_obj(&cam->pos, (t_pt){0, 0, MOVEMENT});
	if (keycode == KEY_S)
		move_obj(&cam->pos, (t_pt){0, 0, -MOVEMENT});
	if (keycode == KEY_A)
		move_obj(&cam->pos, (t_pt){-MOVEMENT, 0, 0});
	if (keycode == KEY_D)
		move_obj(&cam->pos, (t_pt){MOVEMENT, 0, 0});
	if (keycode == KEY_Q)
		move_obj(&cam->pos, (t_pt){0, MOVEMENT, 0});
	if (keycode == KEY_E)
		move_obj(&cam->pos, (t_pt){0, -MOVEMENT, 0});
}

void	move_light(t_light *light, int keycode)
{
	if (keycode == KEY_W)
		move_obj(&light->pos, (t_pt){0, 0, MOVEMENT});
	if (keycode == KEY_S)
		move_obj(&light->pos, (t_pt){0, 0, -MOVEMENT});
	if (keycode == KEY_A)
		move_obj(&light->pos, (t_pt){-MOVEMENT, 0, 0});
	if (keycode == KEY_D)
		move_obj(&light->pos, (t_pt){MOVEMENT, 0, 0});
	if (keycode == KEY_Q)
		move_obj(&light->pos, (t_pt){0, MOVEMENT, 0});
	if (keycode == KEY_E)
		move_obj(&light->pos, (t_pt){0, -MOVEMENT, 0});
}

void	move_sphere(t_sp *sphere, int keycode)
{
	if (keycode == KEY_W)
		move_obj(&sphere->pos, (t_pt){0, 0, MOVEMENT});
	if (keycode == KEY_S)
		move_obj(&sphere->pos, (t_pt){0, 0, -MOVEMENT});
	if (keycode == KEY_A)
		move_obj(&sphere->pos, (t_pt){-MOVEMENT, 0, 0});
	if (keycode == KEY_D)
		move_obj(&sphere->pos, (t_pt){MOVEMENT, 0, 0});
	if (keycode == KEY_Q)
		move_obj(&sphere->pos, (t_pt){0, MOVEMENT, 0});
	if (keycode == KEY_E)
		move_obj(&sphere->pos, (t_pt){0, -MOVEMENT, 0});
}

void	move_plane(t_pl *plane, int keycode)
{
	if (keycode == KEY_W)
		move_obj(&plane->pos, (t_pt){0, 0, MOVEMENT});
	if (keycode == KEY_S)
		move_obj(&plane->pos, (t_pt){0, 0, -MOVEMENT});
	if (keycode == KEY_A)
		move_obj(&plane->pos, (t_pt){-MOVEMENT, 0, 0});
	if (keycode == KEY_D)
		move_obj(&plane->pos, (t_pt){MOVEMENT, 0, 0});
	if (keycode == KEY_Q)
		move_obj(&plane->pos, (t_pt){0, MOVEMENT, 0});
	if (keycode == KEY_E)
		move_obj(&plane->pos, (t_pt){0, -MOVEMENT, 0});
}

void	move_cylinder(t_cy *cylinder, int keycode)
{
	if (keycode == KEY_W)
		move_obj(&cylinder->pos, (t_pt){0, 0, MOVEMENT});
	if (keycode == KEY_S)
		move_obj(&cylinder->pos, (t_pt){0, 0, -MOVEMENT});
	if (keycode == KEY_A)
		move_obj(&cylinder->pos, (t_pt){-MOVEMENT, 0, 0});
	if (keycode == KEY_D)
		move_obj(&cylinder->pos, (t_pt){MOVEMENT, 0, 0});
	if (keycode == KEY_Q)
		move_obj(&cylinder->pos, (t_pt){0, MOVEMENT, 0});
	if (keycode == KEY_E)
		move_obj(&cylinder->pos, (t_pt){0, -MOVEMENT, 0});
}
