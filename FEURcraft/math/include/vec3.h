#ifndef VEC3_H
#define VEC3_H

#define VEC3(_x, _y, _z) ((vec3) {.x = _x, .y = _y, .z = _z})

#define VEC3_ZERO VEC3(0.f, 0.f, 0.f)
#define VEC3_ONE  VEC3(1.f, 1.f, 1.f)

typedef struct vec3 vec3;

struct vec3
{
	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };

		float data[3];
	};
};

vec3 vec3_add  (vec3 u, vec3 v);
vec3 vec3_sub  (vec3 u, vec3 v);
vec3 vec3_cross(vec3 u, vec3 v);

vec3 vec3_add_scal (vec3 u, float l);
vec3 vec3_sub_scal (vec3 u, float l);
vec3 vec3_mult_scal(vec3 u, float l);

vec3 vec3_norm(vec3 u);

void vec3_add_in  (vec3* u, vec3 v);
void vec3_sub_in  (vec3* u, vec3 v);

void vec3_add_scal_in (vec3* u, float l);
void vec3_sub_scal_in (vec3* u, float l);
void vec3_mult_scal_in(vec3* u, float l);

void vec3_norm_in(vec3* u);

float vec3_dot(vec3 u, vec3 v);

float vec3_len (vec3 u);
float vec3_len2(vec3 u);

float vec3_dist (vec3 u, vec3 v);
float vec3_dist2(vec3 u, vec3 v);

#endif // VEC3_H
