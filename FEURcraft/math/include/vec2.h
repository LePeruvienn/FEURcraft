#ifndef VEC2_H
#define VEC2_H

#define VEC2(_x, _y) ((Vec2) {.x = _x, .y = _y})

#define VEC2_ZERO VEC2(0.f, 0.f)
#define VEC2_ONE  VEC2(1.f, 1.f)

typedef struct Vec2 Vec2;

struct Vec2
{
	union
	{
		struct { float x, y; };

		float data[2];
	};
};

Vec2 vec2_add  (Vec2 u, Vec2 v);
Vec2 vec2_sub  (Vec2 u, Vec2 v);

Vec2 vec2_add_scal (Vec2 u, float l);
Vec2 vec2_sub_scal (Vec2 u, float l);
Vec2 vec2_mult_scal(Vec2 u, float l);

Vec2 vec2_norm(Vec2 u);

void vec2_add_in  (Vec2* u, Vec2 v);
void vec2_sub_in  (Vec2* u, Vec2 v);

void vec2_add_scal_in (Vec2* u, float l);
void vec2_sub_scal_in (Vec2* u, float l);
void vec2_mult_scal_in(Vec2* u, float l);

void vec2_norm_in(Vec2* u);

float vec2_dot(Vec2 u, Vec2 v);

float vec2_len (Vec2 u);
float vec2_len2(Vec2 u);

float vec2_dist (Vec2 u, Vec2 v);
float vec2_dist2(Vec2 u, Vec2 v);

#endif // VEC2_H
