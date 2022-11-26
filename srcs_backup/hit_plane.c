/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:32:08 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 21:38:37 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

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
	hit->t = tmp;
	hit->albedo = pl->color;
	hit->pos = vadd(ray.pos, vmult(ray.dir, hit->t));
	hit->n_vec = pl->dir;
	if (vdot(ray.dir, hit->n_vec) > 0)
		hit->n_vec = vmult(hit->n_vec, -1);
	return (TRUE);
}
