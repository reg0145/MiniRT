#include "structs.h"

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

t_pt	vadd(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_pt	vsub(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_pt	vmult(t_pt vec, double t)
{
	return ((t_pt){vec.x * t, vec.y * t, vec.z * t});
}

t_pt	vdiv(t_pt vec, double t)
{
	return ((t_pt){vec.x / t, vec.y / t, vec.z / t});
}

double	vdot(t_pt vec1, t_pt vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_pt	vcross(t_pt vec1, t_pt vec2)
{
	return ((t_pt){vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x});
}

t_pt	vreflect(t_pt vec, t_pt n_vec)
{
	return (vsub(vec, vmult(n_vec, 2 * vdot(vec, n_vec))));
}
