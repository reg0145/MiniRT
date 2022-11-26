/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:32:47 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 12:40:59 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

int	hit_cylinder_side(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	t_pt	op;
	double	a;
	double	b;
	double	c;
	double	tmp;

	op = vsub(ray.pos, cy->pos);
	a = vlength2(vcross(ray.dir, cy->dir));
	b = 2 * vdot(vcross(ray.dir, cy->dir), \
		vcross(op, cy->dir));
	c = vlength2(vcross(op, cy->dir)) - pow(cy->r, 2);
	tmp = root_formula(a, b, c, hit);
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	if (fabs(vdot(vsub(vadd(ray.pos, vmult(ray.dir, tmp)), cy->pos), cy->dir)) \
		 > cy->height / 2) // 원기둥 높이만큼만 나오도록 자르기
		return (FALSE);
	hit->t = tmp;
	hit->t_max = tmp;
	hit->albedo = cy->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = vdiv(vsub(hit->pos, cy->pos), cy->r);
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

int	hit_cylinder_top(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	double	tmp;
	t_pt	top;

	top = vadd(cy->pos, vmult(cy->dir, cy->height / 2));
	tmp = vdot(vsub(top, ray.pos), cy->dir) / vdot(ray.dir, cy->dir);
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	if (vlength2(vsub(vadd(ray.pos, vmult(ray.dir, tmp)), top)) > pow(cy->r, 2))
		return (FALSE);
	hit->t = tmp;
	hit->t_max = tmp;
	hit->albedo = cy->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = cy->dir;
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

int	hit_cylinder_bot(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	double	tmp;
	t_pt	bot;

	bot = vsub(cy->pos, vmult(cy->dir, cy->height / 2));
	tmp = vdot(vsub(bot, ray.pos), cy->dir) / vdot(ray.dir, cy->dir);
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	if (vlength2(vsub(vadd(ray.pos, vmult(ray.dir, tmp)), bot)) > pow(cy->r, 2))
		return (FALSE);
	hit->t = tmp;
	hit->t_max = tmp;
	hit->albedo = cy->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = vmult(cy->dir, -1);
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

/* 구!!!!!!!  현!!!!!!!  필!!!!!!!  요!!!!!!! */
int	hit_cylinder(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	int	return_value;

	return_value = FALSE;
	return_value += hit_cylinder_top(cy, ray, hit);
	return_value += hit_cylinder_bot(cy, ray, hit);
	return_value += hit_cylinder_side(cy, ray, hit);
	return (return_value);
}
