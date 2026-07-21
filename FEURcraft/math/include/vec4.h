#ifndef VEC4_H
#define VEC4_H

#define VEC4(_x, _y, _z, _w) ((Vec4) {.x = _x, .y = _y, .z = _z, .w = _w})

#define VEC4_ZERO VEC4(0.f, 0.f, 0.f, 0.f)
#define VEC4_ONE  VEC4(1.f, 1.f, 1.f, 1.f)

typedef struct Vec4 Vec4;

struct Vec4
{
	union
	{
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };

		float data[4];
	};
};

Vec4 vec4_add  (Vec4 u, Vec4 v);
Vec4 vec4_sub  (Vec4 u, Vec4 v);
Vec4 vec4_cross(Vec4 u, Vec4 v);

Vec4 vec4_add_scal (Vec4 u, float l);
Vec4 vec4_sub_scal (Vec4 u, float l);
Vec4 vec4_mult_scal(Vec4 u, float l);

Vec4 vec4_norm(Vec4 u);

void vec4_add_in  (Vec4* u, Vec4 v);
void vec4_sub_in  (Vec4* u, Vec4 v);

void vec4_add_scal_in (Vec4* u, float l);
void vec4_sub_scal_in (Vec4* u, float l);
void vec4_mult_scal_in(Vec4* u, float l);

void vec4_norm_in(Vec4* u);

float vec4_dot(Vec4 u, Vec4 v);

float vec4_len (Vec4 u);
float vec4_len2(Vec4 u);

float vec4_dist (Vec4 u, Vec4 v);
float vec4_dist2(Vec4 u, Vec4 v);

#endif // VEC4_H
