#ifndef VEC3I_H
#define VEC3I_H

#define VEC3I(_x, _y, _z) ((Vec3i) {.x = _x, .y = _y, .z = _z})

#define VEC3I_ZERO VEC3I(0, 0, 0)
#define VEC3I_ONE  VEC3I(1, 1, 1)

typedef struct Vec3i Vec3i;

struct Vec3i
{
	union
	{
		struct { int x, y, z; };
		int data[3];
	};
};

Vec3i vec3i_add  (Vec3i u, Vec3i v);
Vec3i vec3i_sub  (Vec3i u, Vec3i v);
Vec3i vec3i_cross(Vec3i u, Vec3i v);

Vec3i vec3i_add_scal (Vec3i u, int l);
Vec3i vec3i_sub_scal (Vec3i u, int l);
Vec3i vec3i_mult_scal(Vec3i u, int l);

void vec3i_add_in  (Vec3i* u, Vec3i v);
void vec3i_sub_in  (Vec3i* u, Vec3i v);

void vec3i_add_scal_in (Vec3i* u, int l);
void vec3i_sub_scal_in (Vec3i* u, int l);
void vec3i_mult_scal_in(Vec3i* u, int l);

float vec3i_len (Vec3i u);
int vec3i_len2(Vec3i u);

float vec3i_dist (Vec3i u, Vec3i v);
float vec3i_dist2(Vec3i u, Vec3i v);

#endif // VEC3I_H
