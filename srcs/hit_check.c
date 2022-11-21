/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:42:31 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 16:28:52 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	root_formula(double a, double b, double c, t_hit_check *hit)
{
	double	discriminant;
	double	root1;
	double	root2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	root1 = (-b + sqrt(discriminant)) / (2 * a);
	root2 = (-b - sqrt(discriminant)) / (2 * a);
	if ((root1 < hit->t_min && root2 < hit->t_min) || \
		(root1 > hit->t_max && root2 > hit->t_max))
		return (-1);
	hit->is_surface = FALSE;
	if (discriminant <= 0.03)	// 0.03보다 작으면 표면으로 간주
		hit->is_surface = TRUE;
	if (fmin(root1, root2) > 0)
		return (fmin(root1, root2));
	return (fmax(root1, root2));
}

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

int	hit_plane(t_pl *pl, t_ray ray, t_hit_check *hit)
{
	double	denom;	//직선의 방정식 분모
	double	numer;	//직선의 방정식 분자
	double	tmp;

	denom = vdot(pl->dir, ray.dir);	//평면의 방향 벡터와 광선의 방향 벡터의 내적 (기울기)
	if (fabs(denom) < 1e-6)
		return (FALSE);
	numer = vdot(vsub(pl->pos, ray.pos), pl->dir); //평면의 방향 벡터와 광선의 시작점과 평면의 거리의 내적
	tmp = numer / denom;	//t값
	if (tmp < hit->t_min || hit->t_max <= tmp)
		return (FALSE);
	hit->is_surface = FALSE;
	hit->t = tmp;
	hit->albedo = pl->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = pl->dir;
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}

int	hit_cylinder(t_cy *cy, t_ray ray, t_hit_check *hit)
{
	(void)hit;
	(void)ray;
	(void)cy;
	return (TRUE);
}

int	hit_check(t_obj *obj, t_ray ray, t_hit_check *hit)
{
	int	return_value;

	if (obj->type == SPHERE)
		return_value = hit_sphere((t_sp *)obj->obj_info, ray, hit);
	if (obj->type == PLANE)
		return_value = hit_plane((t_pl *)obj->obj_info, ray, hit);
	if (obj->type == CYLINDER)
		return_value = hit_cylinder((t_cy *)obj->obj_info, ray, hit);
	return (return_value);
}

int	check_objs(t_info *info, t_ray ray, t_hit_check *hit)
{
	t_obj		*obj;
	t_hit_check	tmp;
	t_list		*list;
	int			return_value;

	return_value = FALSE;
	list = info->objs;
	tmp = *hit;
	while (list)
	{
		obj = (t_obj *)list->content;
		if (hit_check(obj, ray, &tmp))
		{
			if (tmp.t_max > tmp.t)
			{
				tmp.t_max = tmp.t;
				return_value = TRUE;
				*hit = tmp;
			}
		}
		list = list->next;
	}
	return (return_value);
}
