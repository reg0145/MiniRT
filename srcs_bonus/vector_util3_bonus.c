/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:22 by nheo              #+#    #+#             */
/*   Updated: 2022/11/27 14:43:01 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_pt	vcross(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - \
		vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x});
}

t_pt	vreflect(t_pt origin, t_pt dir)
{
	return (vsub(origin, vmult(dir, 2 * vdot(origin, dir))));
}

t_pt	vmult_vec(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
}

t_pt	vmin(t_pt vec1, t_pt vec2)
{
	t_pt	min;

	min = vec1;
	if (vec1.x > vec2.x)
		min.x = vec2.x;
	if (vec1.y > vec2.y)
		min.y = vec2.y;
	if (vec1.z > vec2.z)
		min.z = vec2.z;
	return (min);
}
