#include "vec2.h"

#include <math.h>

vec2 vec2_add(vec2 u, vec2 v)
{
	return (vec2)
	{
		.x = (u.x + v.x),
		.y = (u.y + v.y)
	};
}

vec2 vec2_sub(vec2 u, vec2 v)
{
	return (vec2)
	{
		.x = (u.x - v.x),
		.y = (u.y - v.y)
	};
}

vec2 vec2_add_scal(vec2 u, float l)
{
	return (vec2)
	{
		.x = (u.x + l),
		.y = (u.y + l)
	};
}

vec2 vec2_sub_scal(vec2 u, float l)
{
	return (vec2)
	{
		.x = (u.x - l),
		.y = (u.y - l)
	};
}

vec2 vec2_mult_scal(vec2 u, float l)
{
	return (vec2)
	{
		.x = (u.x * l),
		.y = (u.y * l)
	};
}

vec2 vec2_norm(vec2 u)
{
	float len = vec2_len(u);

	if (len == 0)
		return VEC2_ZERO;

	return vec2_mult_scal(u, 1.0f / len);
}

void vec2_add_in(vec2* u, vec2 v)
{
	u->x += v.x;
	u->y += v.y;
}

void vec2_sub_in(vec2* u, vec2 v)
{
	u->x -= v.x;
	u->y -= v.y;
}

void vec2_add_scal_in(vec2* u, float l)
{
	u->x += l;
	u->y += l;
}

void vec2_sub_scal_in(vec2* u, float l)
{
	u->x -= l;
	u->y -= l;
}

void vec2_mult_scal_in(vec2* u, float l)
{
	u->x *= l;
	u->y *= l;
}

void vec2_norm_in(vec2* u)
{
	float len = vec2_len(*u);

	if (len == 0.f)
	{
		u->x = 0.f;
		u->y = 0.f;
		return;
	}

	vec2_mult_scal_in(u, 1 / len);
}

float vec2_dot(vec2 u, vec2 v)
{
	return (u.x * v.x) + (u.y * v.y);
}

float vec2_len(vec2 u)
{
	return sqrtf((u.x * u.x) + (u.y * u.y));
}

float vec2_len2(vec2 u)
{
	return (u.x * u.x) + (u.y * u.y);
}

float vec2_dist(vec2 u, vec2 v)
{
	return vec2_len(VEC2(u.x - v.x, u.y - v.y));
}

float vec2_dist2(vec2 u, vec2 v)
{
	return vec2_len2(VEC2(u.x - v.x, u.y - v.y));
}
