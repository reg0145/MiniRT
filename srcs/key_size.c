/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:52:27 by donghyuk          #+#    #+#             */
/*   Updated: 2022/11/28 16:41:45 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "key_code.h"
#include <math.h>

static void	resize_cylinder(t_cy *cy, int keycode)
{
	if (keycode == KEY_SIZE_UP)
	{
		(*cy).r = (*cy).r + RESIZE;
		(*cy).height = (*cy).height + RESIZE;
	}
	if (keycode == KEY_SIZE_DOWN)
	{
		if ((*cy).r > RESIZE)
			(*cy).r = (*cy).r - RESIZE;
		if ((*cy).height > RESIZE)
			(*cy).height = (*cy).height - RESIZE;
	}
}

static void	resize_sphere(t_sp *sp, int keycode)
{
	if (keycode == KEY_SIZE_UP)
		(*sp).r = (*sp).r + RESIZE;
	if (keycode == KEY_SIZE_DOWN)
	{
		if ((*sp).r > RESIZE)
			(*sp).r = (*sp).r - RESIZE;
	}
}

void	key_size(void *clicked, int type, int keycode)
{
	if (type == CYLINDER)
		resize_cylinder((t_cy *)((t_obj *)clicked)->obj_info, keycode);
	if (type == SPHERE)
		resize_sphere((t_sp *)((t_obj *)clicked)->obj_info, keycode);
}
