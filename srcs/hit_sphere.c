/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:31:28 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 01:44:28 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_sphere(t_sp *sp, t_ray ray, t_hit_check *hit)
{
	t_pt	oc;
	double	a;
	double	b;
	double	c;
	double	tmp;

	oc = vsub(ray.pos, sp->pos);
	a = vlength2(ray.dir);
	b = 2 * vdot(oc, ray.dir);
	c = vlength2(oc) - sp->r * sp->r;
	tmp = root_formula(a, b, c, hit);
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	hit->t = tmp;
	hit->albedo = sp->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = vdiv(vsub(hit->pos, sp->pos), sp->r);
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}
