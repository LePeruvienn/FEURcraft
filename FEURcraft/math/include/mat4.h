#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"

#include <stdint.h>


#define MAT4V(u, v, w, z) ((mat4) { .cols = {u, v, w, z} })

#define MAT4(u1, v1, w1, z1,  \
             u2, v2, w2, z2,  \
             u3, v3, w3, z3,  \
             u4, v4, w4, z4 ) \
	MAT4V( \
		(VEC4(u1, u2, u3, u4)), \
		(VEC4(v1, v2, v3, v4)), \
		(VEC4(w1, w2, w3, w4)), \
		(VEC4(z1, z2, z3, z4))  \
	)

#define MAT4_IDENTITY MAT4(1.f, 0.f, 0.f, 0.f, \
                           0.f, 1.f, 0.f, 0.f, \
                           0.f, 0.f, 1.f, 0.f, \
                           0.f, 0.f, 0.f, 1.f)

#define MAT4_ZERO MAT4(0.f, 0.f, 0.f, 0.f, \
                       0.f, 0.f, 0.f, 0.f, \
                       0.f, 0.f, 0.f, 0.f, \
                       0.f, 0.f, 0.f, 0.f)

typedef struct mat4 mat4;

struct mat4
{
	union
	{
		vec4 cols[4];

		struct
		{
			float m00, m10, m20, m30;
			float m01, m11, m21, m31;
			float m02, m12, m22, m32;
			float m03, m13, m23, m33;
		};

		float data[16];
	};
};

vec4 vec4_mult_mat4(vec4 u, mat4 A);
vec4 mat4_mult_vec4(mat4 A, vec4 u);

vec4 mat4_get_row(mat4 A, unsigned int index);

mat4 mat4_add (mat4 A, mat4 B);
mat4 mat4_sub (mat4 A, mat4 B);
mat4 mat4_mult(mat4 A, mat4 B);

mat4 mat4_add_scal (mat4 A, float l);
mat4 mat4_sub_scal (mat4 A, float l);
mat4 mat4_mult_scal(mat4 A, float l);

mat4 mat4_inv(mat4 A);

mat4 mat4_transpose(mat4 A);

mat4 mat4_scale_x(float s);
mat4 mat4_scale_y(float s);
mat4 mat4_scale_z(float s);

mat4 mat4_scale(float s);

mat4 mat4_translate_x(float t);
mat4 mat4_translate_y(float t);
mat4 mat4_translate_z(float t);

mat4 mat4_translate(vec3 t);

mat4 mat4_rotate_x(float angle);
mat4 mat4_rotate_y(float angle);
mat4 mat4_rotate_z(float angle);

mat4 mat4_rotate(vec3 axis, float angle);

void mat4_add_in (mat4* A, mat4 B);
void mat4_sub_in (mat4* A, mat4 B);
void mat4_mult_in(mat4* A, mat4 B);

void mat4_add_scal_in (mat4* A, float l);
void mat4_sub_scal_in (mat4* A, float l);
void mat4_mult_scal_in(mat4* A, float l);

void mat4_inv_in(mat4* A);

void mat4_transpose_in(mat4* A);

#endif // MAT4_H
