/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:54:05 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 16:36:31 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code.h"
#include "../headers/minirt.h"

static int	check_objs_clicked(t_info *info, t_ray ray, t_hit_check *hit)
{
	t_obj		*obj;
	t_hit_check	tmp;
	t_list		*list;
	int			return_value;

	return_value = FALSE;
	list = info->objs;
	tmp = *hit;
	while (list)
	{
		obj = (t_obj *)list->content;
		if (hit_check(obj, ray, &tmp))
		{
			if (tmp.t_max > tmp.t)
			{
				info->clicked = obj;
				info->clicked_type = obj->type;
				tmp.t_max = tmp.t;
				return_value = TRUE;
				*hit = tmp;
			}
		}
		list = list->next;
	}
	return (return_value);
}

static int	trace_ray(t_info *info, t_ray ray)
{
	t_hit_check	hit;

	ft_memset(&hit, 0, sizeof(t_hit_check));
	hit.t_max = 10000;
	hit.t_min = 1e-6;
	hit.t = hit.t_max;
	if (check_objs_clicked(info, ray, &hit))
		return (TRUE);
	return (FALSE);
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_info	*info;
	t_ray	ray;

	if (button != LEFT_CLICK)
		return (0);
	info = (t_info *)param;
	ray = ray_init(info, (double)x / (WIDTH - 1), \
					(double)y / (HEIGHT - 1));
	if (!trace_ray(info, ray))
		info->clicked = NULL;
	return (0);
}