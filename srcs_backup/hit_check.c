/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:42:31 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 21:38:33 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	root_formula(double a, double b, double c, t_hit_check *hit)
{
	double	discriminant;
	double	root1;
	double	root2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	root1 = (-b + sqrt(discriminant)) / (2 * a);
	root2 = (-b - sqrt(discriminant)) / (2 * a);
	if ((root1 < hit->t_min && root2 < hit->t_min) || \
		(root1 > hit->t_max && root2 > hit->t_max))
		return (-1);
	if (fmin(root1, root2) > 0)
		return (fmin(root1, root2));
	return (fmax(root1, root2));
}

int	hit_check(t_obj *obj, t_ray ray, t_hit_check *hit)
{
	int	return_value;

	if (obj->type == SPHERE)
		return_value = hit_sphere((t_sp *)obj->obj_info, ray, hit);
	if (obj->type == PLANE)
		return_value = hit_plane((t_pl *)obj->obj_info, ray, hit);
	if (obj->type == CYLINDER)
		return_value = hit_cylinder((t_cy *)obj->obj_info, ray, hit);
	return (return_value);
}

int	check_objs(t_info *info, t_ray ray, t_hit_check *hit)
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
				tmp.t_max = tmp.t;
				return_value = TRUE;
				*hit = tmp;
			}
		}
		list = list->next;
	}
	return (return_value);
}
