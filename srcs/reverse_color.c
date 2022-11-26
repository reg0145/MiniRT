/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:57:15 by nheo              #+#    #+#             */
/*   Updated: 2022/11/23 13:57:40 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reverse_color(t_obj *obj)
{
	t_sp	*spere;
	t_pl	*plane;
	t_cy	*cylinder;

	if (obj->type == SPHERE)
	{
		spere = (t_sp *)obj->obj_info;
		spere->color = (t_pt){1 - spere->color.x, \
			1 - spere->color.y, 1 - spere->color.z};
	}
	else if (obj->type == PLANE)
	{
		plane = (t_pl *)obj->obj_info;
		plane->color = (t_pt){1 - plane->color.x, \
			1 - plane->color.y, 1 - plane->color.z};
	}
	else if (obj->type == CYLINDER)
	{
		cylinder = (t_cy *)obj->obj_info;
		cylinder->color = (t_pt){1 - cylinder->color.x, \
			1 - cylinder->color.y, 1 - cylinder->color.z};
	}
}
