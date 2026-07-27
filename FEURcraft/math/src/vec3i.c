#include "vec3i.h"

#include <math.h>

Vec3i vec3i_add(Vec3i u, Vec3i v)
{
	return (Vec3i)
	{
		.x = (u.x + v.x),
		.y = (u.y + v.y),
		.z = (u.z + v.z)
	};
}

Vec3i vec3i_sub(Vec3i u, Vec3i v)
{
	return (Vec3i)
	{
		.x = (u.x - v.x),
		.y = (u.y - v.y),
		.z = (u.z - v.z)
	};
}

Vec3i vec3i_cross(Vec3i u, Vec3i v)
{
	return (Vec3i)
	{
		.x = ((u.y * v.z) - (u.z * v.y)),
		.y = ((u.z * v.x) - (u.x * v.z)),
		.z = ((u.x * v.y) - (u.y * v.x))
	};
}

Vec3i vec3i_add_scal(Vec3i u, int l)
{
	return (Vec3i)
	{
		.x = (u.x + l),
		.y = (u.y + l),
		.z = (u.z + l)
	};
}

Vec3i vec3i_sub_scal(Vec3i u, int l)
{
	return (Vec3i)
	{
		.x = (u.x - l),
		.y = (u.y - l),
		.z = (u.z - l)
	};
}

Vec3i vec3i_mult_scal(Vec3i u, int l)
{
	return (Vec3i)
	{
		.x = (u.x * l),
		.y = (u.y * l),
		.z = (u.z * l)
	};
}

Vec3i vec3i_norm(Vec3i u)
{
	float len = vec3i_len(u);

	if (len == 0.f)
		return VEC3I_ZERO;

	return vec3i_mult_scal(u, 1 / len);
}

void vec3i_add_in(Vec3i* u, Vec3i v)
{
	u->x += v.x;
	u->y += v.y;
	u->z += v.z;
}
void vec3i_sub_in(Vec3i* u, Vec3i v)
{
	u->x -= v.x;
	u->y -= v.y;
	u->z -= v.z;
}

void vec3i_add_scal_in(Vec3i* u, int l)
{
	u->x += l;
	u->y += l;
	u->z += l;
}

void vec3i_sub_scal_in(Vec3i* u, int l)
{
	u->x -= l;
	u->y -= l;
	u->z -= l;
}

void vec3i_mult_scal_in(Vec3i* u, int l)
{
	u->x *= l;
	u->y *= l;
	u->z *= l;
}

float vec3i_len(Vec3i u)
{
	return sqrtf((float) (u.x * u.x) + (u.y * u.y) + (u.z * u.z));
}

int vec3i_len2(Vec3i u)
{
	return (u.x * u.x) + (u.y * u.y) + (u.z * u.z);
}

float vec3i_dist (Vec3i u, Vec3i v)
{
	return vec3i_len(VEC3I(u.x - v.x, u.y - v.y, u.z - v.z));
}

float vec3i_dist2(Vec3i u, Vec3i v)
{
	return vec3i_len2(VEC3I(u.x - v.x, u.y - v.y, u.z - v.z));
}

