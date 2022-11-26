/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:31:28 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 20:31:37 by nheo             ###   ########.fr       */
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

	oc = vsub(ray.pos, sp->pos); //광선의 시작점 - 구의 중심
	a = vlength2(ray.dir);	//광선의 방향 벡터의 길이의 제곱
	b = 2 * vdot(oc, ray.dir); //광선의 방향 벡터와 oc의 내적 * 2
	c = vlength2(oc) - sp->r * sp->r; //oc의 길이의 제곱 - 구의 반지름의 제곱
	tmp = root_formula(a, b, c, hit); // t값 최대, 최소 범위 내에서의 광선과 구의 교점(근의 공식)
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
