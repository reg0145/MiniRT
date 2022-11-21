/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minor_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:55:52 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 17:34:56 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char **args, t_info *info)
{
	t_obj	*obj;
	t_sp	*new_sp;
	t_list	*new;

	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'sp' must be 4 arguments");
	obj = (t_obj *)malloc(sizeof(t_obj));
	new_sp = (t_sp *)malloc(sizeof(t_sp));
	if (!obj || !new_sp)
		ft_error("malloc failed");
	new_sp->pos = parse_pt(args[1]);
	new_sp->r = ft_atod(args[2]) / 2;
	new_sp->color = parse_color(args[3]);
	obj->obj_info = new_sp;
	obj->type = SPHERE;
	new = ft_lstnew(obj);
	if (!new)
		ft_error("malloc failed");
	ft_lstadd_back(&info->objs, new);
}

void	parse_plane(char **args, t_info *info)
{
	t_obj	*obj;
	t_pl	*new_pl;
	t_list	*new;

	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'pl' must be 4 arguments");
	obj = (t_obj *)malloc(sizeof(t_obj));
	new_pl = (t_pl *)malloc(sizeof(t_pl));
	if (!obj || !new_pl)
		ft_error("malloc failed");
	new_pl->pos = parse_pt(args[1]);
	new_pl->dir = parse_pt(args[2]);
	if (new_pl->dir.x < -1 || new_pl->dir.x > 1 || new_pl->dir.y < -1 || \
		new_pl->dir.y > 1 || new_pl->dir.z < -1 || new_pl->dir.z > 1)
		ft_error("wrong input : plane normal vector must be -1 ~ 1");
	new_pl->color = parse_color(args[3]);
	obj->type = PLANE;
	obj->obj_info = new_pl;
	new = ft_lstnew(obj);
	if (!new)
		ft_error("malloc failed");
	ft_lstadd_back(&info->objs, new);
}

void	parse_cylinder(char **args, t_info *info)
{
	t_obj	*obj;
	t_cy	*new_cy;
	t_list	*new;

	if (ft_strslen(args) != 6)
		ft_error("wrong input : 'cy' must be 6 arguments");
	obj = (t_obj *)malloc(sizeof(t_obj));
	new_cy = (t_cy *)malloc(sizeof(t_cy));
	if (!obj || !new_cy)
		ft_error("malloc failed");
	new_cy->pos = parse_pt(args[1]);
	new_cy->dir = parse_pt(args[2]);
	if (new_cy->dir.x < -1 || new_cy->dir.x > 1 || new_cy->dir.y < -1 || \
		new_cy->dir.y > 1 || new_cy->dir.z < -1 || new_cy->dir.z > 1)
		ft_error("wrong input : cylinder normal vector must be -1 ~ 1");
	new_cy->r = ft_atod(args[3]) / 2;
	new_cy->height = ft_atod(args[4]);
	new_cy->color = parse_color(args[5]);
	obj->type = CYLINDER;
	obj->obj_info = new_cy;
	new = ft_lstnew(obj);
	if (!new)
		ft_error("malloc failed");
	ft_lstadd_back(&info->objs, new);
}
