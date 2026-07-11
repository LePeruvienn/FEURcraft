#include "vec4.h"

#include <math.h>

vec4 vec4_add(vec4 u, vec4 v)
{
	return (vec4)
	{
		.x = (u.x + v.x),
		.y = (u.y + v.y),
		.z = (u.z + v.z),
		.w = (u.w + v.w)
	};
}

vec4 vec4_sub(vec4 u, vec4 v)
{
	return (vec4)
	{
		.x = (u.x - v.x),
		.y = (u.y - v.y),
		.z = (u.z - v.z),
		.w = (u.w - v.w)
	};
}

vec4 vec4_add_scal(vec4 u, float l)
{
	return (vec4)
	{
		.x = (u.x + l),
		.y = (u.y + l),
		.z = (u.z + l),
		.w = (u.w + l)
	};
}

vec4 vec4_sub_scal(vec4 u, float l)
{
	return (vec4)
	{
		.x = (u.x - l),
		.y = (u.y - l),
		.z = (u.z - l),
		.w = (u.w - l)
	};
}

vec4 vec4_mult_scal(vec4 u, float l)
{
	return (vec4)
	{
		.x = (u.x * l),
		.y = (u.y * l),
		.z = (u.z * l),
		.w = (u.w * l)
	};
}

vec4 vec4_norm(vec4 u)
{
	float len = vec4_len(u);

	if (len == 0.f)
		return VEC4_ZERO;

	return vec4_mult_scal(u, 1 / len);
}

void vec4_add_in(vec4* u, vec4 v)
{
	u->x += v.x;
	u->y += v.y;
	u->z += v.z;
	u->w += v.w;
}

void vec4_sub_in(vec4* u, vec4 v)
{
	u->x -= v.x;
	u->y -= v.y;
	u->z -= v.z;
	u->w -= v.w;
}

void vec4_add_scal_in(vec4* u, float l)
{
	u->x += l;
	u->y += l;
	u->z += l;
	u->w += l;
}

void vec4_sub_scal_in(vec4* u, float l)
{
	u->x -= l;
	u->y -= l;
	u->z -= l;
	u->w -= l;
}

void vec4_mult_scal_in(vec4* u, float l)
{
	u->x *= l;
	u->y *= l;
	u->z *= l;
	u->w *= l;
}

void vec4_norm_in(vec4* u)
{
	float len = vec4_len(*u);

	if (len == 0.f)
	{
		u->x = 0.f;
		u->y = 0.f;
		u->z = 0.f;
		u->w = 0.f;
		return;
	}

	vec4_mult_scal_in(u, 1 / len);
}

float vec4_dot(vec4 u, vec4 v)
{
	return (u.x * v.x)
	     + (u.y * v.y)
	     + (u.z * v.z)
	     + (u.w * v.w);
}

float vec4_len(vec4 u)
{
	return sqrtf(vec4_len2(u));
}

float vec4_len2(vec4 u)
{
	return (u.x * u.x)
	     + (u.y * u.y)
	     + (u.z * u.z)
	     + (u.w * u.w);
}

float vec4_dist(vec4 u, vec4 v)
{
	return vec4_len(VEC4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w));
}

float vec4_dist2(vec4 u, vec4 v)
{
	return vec4_len2(VEC4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w));
}

