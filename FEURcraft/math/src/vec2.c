#include "vec2.h"

#include <math.h>

Vec2 vec2_add(Vec2 u, Vec2 v)
{
	return (Vec2)
	{
		.x = (u.x + v.x),
		.y = (u.y + v.y)
	};
}

Vec2 vec2_sub(Vec2 u, Vec2 v)
{
	return (Vec2)
	{
		.x = (u.x - v.x),
		.y = (u.y - v.y)
	};
}

Vec2 vec2_add_scal(Vec2 u, float l)
{
	return (Vec2)
	{
		.x = (u.x + l),
		.y = (u.y + l)
	};
}

Vec2 vec2_sub_scal(Vec2 u, float l)
{
	return (Vec2)
	{
		.x = (u.x - l),
		.y = (u.y - l)
	};
}

Vec2 vec2_mult_scal(Vec2 u, float l)
{
	return (Vec2)
	{
		.x = (u.x * l),
		.y = (u.y * l)
	};
}

Vec2 vec2_norm(Vec2 u)
{
	float len = vec2_len(u);

	if (len == 0)
		return VEC2_ZERO;

	return vec2_mult_scal(u, 1.0f / len);
}

void vec2_add_in(Vec2* u, Vec2 v)
{
	u->x += v.x;
	u->y += v.y;
}

void vec2_sub_in(Vec2* u, Vec2 v)
{
	u->x -= v.x;
	u->y -= v.y;
}

void vec2_add_scal_in(Vec2* u, float l)
{
	u->x += l;
	u->y += l;
}

void vec2_sub_scal_in(Vec2* u, float l)
{
	u->x -= l;
	u->y -= l;
}

void vec2_mult_scal_in(Vec2* u, float l)
{
	u->x *= l;
	u->y *= l;
}

void vec2_norm_in(Vec2* u)
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

float vec2_dot(Vec2 u, Vec2 v)
{
	return (u.x * v.x) + (u.y * v.y);
}

float vec2_len(Vec2 u)
{
	return sqrtf((u.x * u.x) + (u.y * u.y));
}

float vec2_len2(Vec2 u)
{
	return (u.x * u.x) + (u.y * u.y);
}

float vec2_dist(Vec2 u, Vec2 v)
{
	return vec2_len(VEC2(u.x - v.x, u.y - v.y));
}

float vec2_dist2(Vec2 u, Vec2 v)
{
	return vec2_len2(VEC2(u.x - v.x, u.y - v.y));
}
