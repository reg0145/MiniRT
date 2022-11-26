/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:32:08 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 12:11:03 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

int	hit_plane(t_pl *pl, t_ray ray, t_hit_check *hit)
{
	double	denom;
	double	numer;
	double	tmp;

	denom = vdot(pl->dir, ray.dir);
	if (fabs(denom) < 1e-6)
		return (FALSE);
	numer = vdot(vsub(pl->pos, ray.pos), pl->dir);
	tmp = numer / denom;
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
