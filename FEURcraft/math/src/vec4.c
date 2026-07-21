#include "vec4.h"

#include <math.h>

Vec4 vec4_add(Vec4 u, Vec4 v)
{
	return (Vec4)
	{
		.x = (u.x + v.x),
		.y = (u.y + v.y),
		.z = (u.z + v.z),
		.w = (u.w + v.w)
	};
}

Vec4 vec4_sub(Vec4 u, Vec4 v)
{
	return (Vec4)
	{
		.x = (u.x - v.x),
		.y = (u.y - v.y),
		.z = (u.z - v.z),
		.w = (u.w - v.w)
	};
}

Vec4 vec4_add_scal(Vec4 u, float l)
{
	return (Vec4)
	{
		.x = (u.x + l),
		.y = (u.y + l),
		.z = (u.z + l),
		.w = (u.w + l)
	};
}

Vec4 vec4_sub_scal(Vec4 u, float l)
{
	return (Vec4)
	{
		.x = (u.x - l),
		.y = (u.y - l),
		.z = (u.z - l),
		.w = (u.w - l)
	};
}

Vec4 vec4_mult_scal(Vec4 u, float l)
{
	return (Vec4)
	{
		.x = (u.x * l),
		.y = (u.y * l),
		.z = (u.z * l),
		.w = (u.w * l)
	};
}

Vec4 vec4_norm(Vec4 u)
{
	float len = vec4_len(u);

	if (len == 0.f)
		return VEC4_ZERO;

	return vec4_mult_scal(u, 1 / len);
}

void vec4_add_in(Vec4* u, Vec4 v)
{
	u->x += v.x;
	u->y += v.y;
	u->z += v.z;
	u->w += v.w;
}

void vec4_sub_in(Vec4* u, Vec4 v)
{
	u->x -= v.x;
	u->y -= v.y;
	u->z -= v.z;
	u->w -= v.w;
}

void vec4_add_scal_in(Vec4* u, float l)
{
	u->x += l;
	u->y += l;
	u->z += l;
	u->w += l;
}

void vec4_sub_scal_in(Vec4* u, float l)
{
	u->x -= l;
	u->y -= l;
	u->z -= l;
	u->w -= l;
}

void vec4_mult_scal_in(Vec4* u, float l)
{
	u->x *= l;
	u->y *= l;
	u->z *= l;
	u->w *= l;
}

void vec4_norm_in(Vec4* u)
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

float vec4_dot(Vec4 u, Vec4 v)
{
	return (u.x * v.x)
	     + (u.y * v.y)
	     + (u.z * v.z)
	     + (u.w * v.w);
}

float vec4_len(Vec4 u)
{
	return sqrtf(vec4_len2(u));
}

float vec4_len2(Vec4 u)
{
	return (u.x * u.x)
	     + (u.y * u.y)
	     + (u.z * u.z)
	     + (u.w * u.w);
}

float vec4_dist(Vec4 u, Vec4 v)
{
	return vec4_len(VEC4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w));
}

float vec4_dist2(Vec4 u, Vec4 v)
{
	return vec4_len2(VEC4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w));
}

