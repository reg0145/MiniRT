/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:32:47 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 21:00:52 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

int	hit_cylinder(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	t_pt	op;
	double	a;
	double	b;
	double	c;
	double	tmp;

	op = vsub(ray.pos, cy->pos);
	a = vlength2(vcross(ray.dir, cy->dir));
	b = 2 * vdot(vcross(ray.dir, cy->dir), \
		vsub(op, vmult(cy->dir, vdot(op, cy->dir))));
	c = vlength2(vcross(op, cy->dir)) - pow(cy->r, 2);
	tmp = root_formula(a, b, c, hit);
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	hit->t = tmp;
	hit->albedo = cy->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = vdiv(vsub(hit->pos, cy->pos), cy->r);
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}
