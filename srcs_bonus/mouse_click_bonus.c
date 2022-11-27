/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:54:05 by nheo              #+#    #+#             */
/*   Updated: 2022/11/27 14:48:12 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code_bonus.h"
#include "minirt_bonus.h"

static void	renew_hit(t_info *info, t_obj *obj, t_obj **hit_obj)
{
	info->clicked = obj;
	info->clicked_type = obj->type;
	*hit_obj = obj;
}

static int	check_objs_clicked(t_info *info, t_ray ray, \
	t_hit_check *hit, t_obj	**hit_obj)
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
			if (tmp.t < hit->t_max)
			{
				renew_hit(info, obj, hit_obj);
				return_value = TRUE;
				*hit = tmp;
			}
		}
		list = list->next;
	}
	return (return_value);
}

static int	trace_ray_clicked(t_info *info, t_ray ray)
{
	t_obj		*hit_obj;
	t_hit_check	hit;

	ft_memset(&hit, 0, sizeof(t_hit_check));
	hit.t_max = 10000;
	hit.t_min = 1e-6;
	hit.t = hit.t_max;
	if (check_objs_clicked(info, ray, &hit, &hit_obj))
	{
		reverse_color(hit_obj);
		return (TRUE);
	}
	return (FALSE);
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_info	*info;
	t_ray	ray;

	if (button != LEFT_CLICK || x > WIDTH || y > HEIGHT || \
		x < 0 || y < 0)
		return (0);
	info = (t_info *)param;
	if (info->clicked && (info->clicked_type == SPHERE || \
		info->clicked_type == PLANE || info->clicked_type == CYLINDER))
		reverse_color(info->clicked);
	ray = ray_init(info, (double)x / (WIDTH - 1), \
					(double)y / (HEIGHT - 1));
	if (!trace_ray_clicked(info, ray))
		info->clicked = NULL;
	draw(info);
	return (0);
}
