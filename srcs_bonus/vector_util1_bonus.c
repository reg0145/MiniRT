/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:31:01 by nheo              #+#    #+#             */
/*   Updated: 2022/11/27 14:43:01 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_pt	vadd(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_pt	vsub(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_pt	vmult(t_pt vec, double t)
{
	return ((t_pt){vec.x * t, vec.y * t, vec.z * t});
}

t_pt	vdiv(t_pt vec, double t)
{
	return ((t_pt){vec.x / t, vec.y / t, vec.z / t});
}

double	vdot(t_pt vec1, t_pt vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
