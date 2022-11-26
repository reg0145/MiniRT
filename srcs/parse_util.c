/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:31:08 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 11:27:55 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_n_vec(t_pt vec)
{
	t_pt	tmp;

	tmp = vunit(vec);
	if (tmp.x != vec.x || tmp.y != vec.y || tmp.z != vec.z)
		ft_error("vector is not normalized");
}

static void	check_sep(char *str, char sep, int num)
{
	while (*str && num)
	{
		if (*str == sep)
			num--;
		str++;
	}
	if (num)
		ft_error("wrong input : wrong number of separators");	
}

t_pt	parse_color(char *str)
{
	char	**colors;
	t_pt	color;

	check_sep(str, ',', 2);
	colors = ft_split(str, ',');
	if (!colors)
		ft_error("malloc failed");
	if (ft_strslen(colors) != 3)
		ft_error("wrong input : color must be 3 numbers");
	color = (t_pt){ft_atod(colors[0]), ft_atod(colors[1]), ft_atod(colors[2])};
	ft_free_strs(colors);
	if (color.z < 0 || color.z > 255 || color.y < 0 || color.y > 255 || \
		color.x < 0 || color.x > 255)
		ft_error("wrong input : color must be 0 ~ 255");
	color = (t_pt){color.x / 255.0, color.y / 255.0, color.z / 255.0};
	return (color);
}

t_pt	parse_pt(char *str)
{
	char	**pts;
	t_pt	pt;

	check_sep(str, ',', 2);
	pts = ft_split(str, ',');
	if (!pts)
		ft_error("malloc failed");
	if (ft_strslen(pts) != 3)
		ft_error("wrong input : point must be 3 numbers");
	pt = ((t_pt){ft_atod(pts[0]), ft_atod(pts[1]), ft_atod(pts[2])});
	ft_free_strs(pts);
	return (pt);
}

t_pt	parse_n_vec(char *str)
{
	t_pt	vec;

	vec = parse_pt(str);
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || vec.y > 1 || \
		vec.z < -1 || vec.z > 1)
		ft_error("wrong input : vector must be -1 ~ 1");
	return (vec);
}
