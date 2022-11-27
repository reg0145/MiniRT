/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:04 by nheo              #+#    #+#             */
/*   Updated: 2022/11/27 14:43:01 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

double	vlength2(t_pt vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vlength(t_pt vec)
{
	return (sqrt(vlength2(vec)));
}

t_pt	vunit(t_pt vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
		ft_error("vector length is 0");
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}
