/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:32:47 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 19:09:00 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

static t_pt	hit_cylinder_side2(t_cy *cy, t_hit_check *hit)
{
	t_pt	tmp2;

	tmp2 = vsub(hit->pos, cy->pos);
	return (vunit(vsub(tmp2, vmult(cy->dir, vdot(cy->dir, tmp2)))));
}

static int	hit_cylinder_side(t_cy *cy, t_ray ray, t_hit_check *hit)
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
		> cy->height / 2)
		return (FALSE);
	hit->t = tmp;
	hit->t_max = tmp;
	hit->albedo = cy->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = hit_cylinder_side2(cy, hit);
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

static int	hit_cylinder_top(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	double	tmp;
	double	len;
	t_pt	top;

	top = vadd(cy->pos, vmult(cy->dir, cy->height / 2));
	tmp = vdot(vsub(top, ray.pos), cy->dir) / vdot(ray.dir, cy->dir);
	hit->is_surface = FALSE;
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	len = vlength2(vsub(vadd(ray.pos, vmult(ray.dir, tmp)), top));
	if (len > pow(cy->r, 2))
		return (FALSE);
	if (pow(cy->r, 2) - len < 0.02)
		hit->is_surface = TRUE;
	hit->t = tmp;
	hit->t_max = tmp;
	hit->albedo = cy->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = cy->dir;
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

static int	hit_cylinder_bot(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	double	tmp;
	double	len;
	t_pt	bot;

	bot = vadd(cy->pos, vmult(cy->dir, -(cy->height / 2)));
	tmp = vdot(vsub(bot, ray.pos), cy->dir) / vdot(ray.dir, cy->dir);
	hit->is_surface = FALSE;
	if (tmp < hit->t_min || hit->t_max < tmp)
		return (FALSE);
	len = vlength2(vsub(vadd(ray.pos, vmult(ray.dir, tmp)), bot));
	if (len > pow(cy->r, 2))
		return (FALSE);
	if (pow(cy->r, 2) - len < 0.02)
		hit->is_surface = TRUE;
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
	if (return_value)
		hit->is_surface = FALSE;
	return (return_value);
}
