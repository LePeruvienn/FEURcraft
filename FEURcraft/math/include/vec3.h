#ifndef VEC3_H
#define VEC3_H

#define VEC3(_x, _y, _z) ((Vec3) {.x = _x, .y = _y, .z = _z})

#define VEC3_ZERO VEC3(0.f, 0.f, 0.f)
#define VEC3_ONE  VEC3(1.f, 1.f, 1.f)

typedef struct Vec3 Vec3;

struct Vec3
{
	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };

		float data[3];
	};
};

Vec3 vec3_add  (Vec3 u, Vec3 v);
Vec3 vec3_sub  (Vec3 u, Vec3 v);
Vec3 vec3_cross(Vec3 u, Vec3 v);

Vec3 vec3_add_scal (Vec3 u, float l);
Vec3 vec3_sub_scal (Vec3 u, float l);
Vec3 vec3_mult_scal(Vec3 u, float l);

Vec3 vec3_norm(Vec3 u);

void vec3_add_in  (Vec3* u, Vec3 v);
void vec3_sub_in  (Vec3* u, Vec3 v);

void vec3_add_scal_in (Vec3* u, float l);
void vec3_sub_scal_in (Vec3* u, float l);
void vec3_mult_scal_in(Vec3* u, float l);

void vec3_norm_in(Vec3* u);

float vec3_dot(Vec3 u, Vec3 v);

float vec3_len (Vec3 u);
float vec3_len2(Vec3 u);

float vec3_dist (Vec3 u, Vec3 v);
float vec3_dist2(Vec3 u, Vec3 v);

#endif // VEC3_H
