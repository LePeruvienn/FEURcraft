#include "vec3.h"

#include <math.h>

vec3 vec3_add(vec3 u, vec3 v)
{
	return (vec3)
	{
		.x = (u.x + v.x),
		.y = (u.y + v.y),
		.z = (u.z + v.z)
	};
}

vec3 vec3_sub(vec3 u, vec3 v)
{
	return (vec3)
	{
		.x = (u.x - v.x),
		.y = (u.y - v.y),
		.z = (u.z - v.z)
	};
}

vec3 vec3_cross(vec3 u, vec3 v)
{
	return (vec3)
	{
		.x = ((u.y * v.z) - (u.z * v.y)),
		.y = ((u.z * v.x) - (u.x * v.z)),
		.z = ((u.x * v.y) - (u.y * v.x))
	};
}

vec3 vec3_add_scal(vec3 u, float l)
{
	return (vec3)
	{
		.x = (u.x + l),
		.y = (u.y + l),
		.z = (u.z + l)
	};
}

vec3 vec3_sub_scal(vec3 u, float l)
{
	return (vec3)
	{
		.x = (u.x - l),
		.y = (u.y - l),
		.z = (u.z - l)
	};
}

vec3 vec3_mult_scal(vec3 u, float l)
{
	return (vec3)
	{
		.x = (u.x * l),
		.y = (u.y * l),
		.z = (u.z * l)
	};
}

vec3 vec3_norm(vec3 u)
{
	float len = vec3_len(u);

	if (len == 0.f)
		return VEC3_ZERO;

	return vec3_mult_scal(u, 1 / len);
}

void vec3_add_in(vec3* u, vec3 v)
{
	u->x += v.x;
	u->y += v.y;
	u->z += v.z;
}
void vec3_sub_in(vec3* u, vec3 v)
{
	u->x -= v.x;
	u->y -= v.y;
	u->z -= v.z;
}

void vec3_add_scal_in(vec3* u, float l)
{
	u->x += l;
	u->y += l;
	u->z += l;
}

void vec3_sub_scal_in(vec3* u, float l)
{
	u->x -= l;
	u->y -= l;
	u->z -= l;
}

void vec3_mult_scal_in(vec3* u, float l)
{
	u->x *= l;
	u->y *= l;
	u->z *= l;
}

float vec3_dot(vec3 u, vec3 v)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

void vec3_norm_in(vec3* u)
{
	float len = vec3_len(*u);

	if (len == 0.f)
	{
		u->x = 0.f;
		u->y = 0.f;
		u->z = 0.f;
		return;
	}

	vec3_mult_scal_in(u, 1 / len);
}

float vec3_len (vec3 u)
{
	return sqrtf((u.x * u.x) + (u.y * u.y) + (u.z * u.z));
}

float vec3_len2(vec3 u)
{
	return (u.x * u.x) + (u.y * u.y) + (u.z * u.z);
}

float vec3_dist (vec3 u, vec3 v)
{
	return vec3_len(VEC3(u.x - v.x, u.y - v.y, u.z - v.z));
}

float vec3_dist2(vec3 u, vec3 v)
{
	return vec3_len2(VEC3(u.x - v.x, u.y - v.y, u.z - v.z));
}

