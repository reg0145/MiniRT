/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_major_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:38:22 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 19:44:21 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char **args, t_info *info)
{
	if (ft_strslen(args) != 3)
		ft_error("wrong input : 'A' must be 3 arguments");
	info->amb.ratio = ft_atod(args[1]);
	if (info->amb.ratio < 0 || info->amb.ratio > 1)
		ft_error("wrong input : ambient ratio must be 0 ~ 1");
	info->amb.color = parse_color(args[2]);
}

void	parse_camera(char **args, t_info *info)
{
	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'C' must be 4 arguments");
	info->cam.pos = parse_pt(args[1]);
	info->cam.dir = parse_pt(args[2]);
	check_n_vec(info->cam.dir);
	info->cam.fov = ft_atod(args[3]);
}

void	parse_light(char **args, t_info *info)
{
	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'L' must be 4 arguments");
	info->light.pos = parse_pt(args[1]);
	info->light.ratio = ft_atod(args[2]);
	if (info->light.ratio < 0 || info->light.ratio > 1)
		ft_error("wrong input : light ratio must be 0 ~ 1");
	info->light.color = parse_color(args[3]);
}
