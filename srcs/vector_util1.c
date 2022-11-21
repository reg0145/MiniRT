/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:31:01 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 14:15:49 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
