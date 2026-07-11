#ifndef VEC4_H
#define VEC4_H

#define VEC4(_x, _y, _z, _w) ((vec4) {.x = _x, .y = _y, .z = _z, .w = _w})

#define VEC4_ZERO VEC4(0.f, 0.f, 0.f, 0.f)
#define VEC4_ONE  VEC4(1.f, 1.f, 1.f, 1.f)

typedef struct vec4 vec4;

struct vec4
{
	union
	{
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };

		float data[4];
	};
};

vec4 vec4_add  (vec4 u, vec4 v);
vec4 vec4_sub  (vec4 u, vec4 v);
vec4 vec4_cross(vec4 u, vec4 v);

vec4 vec4_add_scal (vec4 u, float l);
vec4 vec4_sub_scal (vec4 u, float l);
vec4 vec4_mult_scal(vec4 u, float l);

vec4 vec4_norm(vec4 u);

void vec4_add_in  (vec4* u, vec4 v);
void vec4_sub_in  (vec4* u, vec4 v);

void vec4_add_scal_in (vec4* u, float l);
void vec4_sub_scal_in (vec4* u, float l);
void vec4_mult_scal_in(vec4* u, float l);

void vec4_norm_in(vec4* u);

float vec4_dot(vec4 u, vec4 v);

float vec4_len (vec4 u);
float vec4_len2(vec4 u);

float vec4_dist (vec4 u, vec4 v);
float vec4_dist2(vec4 u, vec4 v);

#endif // VEC4_H
