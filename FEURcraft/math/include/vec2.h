#ifndef VEC2_H
#define VEC2_H

#define VEC2(_x, _y) ((vec2) {.x = _x, .y = _y})

#define VEC2_ZERO VEC2(0.f, 0.f)
#define VEC2_ONE  VEC2(1.f, 1.f)

typedef struct vec2 vec2;

struct vec2
{
	union
	{
		struct { float x, y; };

		float data[2];
	};
};

vec2 vec2_add  (vec2 u, vec2 v);
vec2 vec2_sub  (vec2 u, vec2 v);

vec2 vec2_add_scal (vec2 u, float l);
vec2 vec2_sub_scal (vec2 u, float l);
vec2 vec2_mult_scal(vec2 u, float l);

vec2 vec2_norm(vec2 u);

void vec2_add_in  (vec2* u, vec2 v);
void vec2_sub_in  (vec2* u, vec2 v);

void vec2_add_scal_in (vec2* u, float l);
void vec2_sub_scal_in (vec2* u, float l);
void vec2_mult_scal_in(vec2* u, float l);

void vec2_norm_in(vec2* u);

float vec2_dot(vec2 u, vec2 v);

float vec2_len (vec2 u);
float vec2_len2(vec2 u);

float vec2_dist (vec2 u, vec2 v);
float vec2_dist2(vec2 u, vec2 v);

#endif // VEC2_H
