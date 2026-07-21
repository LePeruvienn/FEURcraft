#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"

#include <stdint.h>


#define MAT4V(u, v, w, z) ((Mat4) { .cols = {u, v, w, z} })

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

typedef struct Mat4 Mat4;

struct Mat4
{
	union
	{
		Vec4 cols[4];

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

Vec4 vec4_mult_mat4(Vec4 u, Mat4 A);
Vec4 mat4_mult_vec4(Mat4 A, Vec4 u);

Vec4 mat4_get_row(Mat4 A, unsigned int index);

Mat4 mat4_add (Mat4 A, Mat4 B);
Mat4 mat4_sub (Mat4 A, Mat4 B);
Mat4 mat4_mult(Mat4 A, Mat4 B);

Mat4 mat4_add_scal (Mat4 A, float l);
Mat4 mat4_sub_scal (Mat4 A, float l);
Mat4 mat4_mult_scal(Mat4 A, float l);

Mat4 mat4_inv(Mat4 A);

Mat4 mat4_transpose(Mat4 A);

Mat4 mat4_scale_x(float s);
Mat4 mat4_scale_y(float s);
Mat4 mat4_scale_z(float s);

Mat4 mat4_scale(float s);

Mat4 mat4_translate_x(float t);
Mat4 mat4_translate_y(float t);
Mat4 mat4_translate_z(float t);

Mat4 mat4_translate(Vec3 t);

Mat4 mat4_rotate_x(float angle);
Mat4 mat4_rotate_y(float angle);
Mat4 mat4_rotate_z(float angle);

Mat4 mat4_rotate(Vec3 axis, float angle);

void mat4_add_in (Mat4* A, Mat4 B);
void mat4_sub_in (Mat4* A, Mat4 B);

void mat4_add_scal_in (Mat4* A, float l);
void mat4_sub_scal_in (Mat4* A, float l);
void mat4_mult_scal_in(Mat4* A, float l);

void mat4_inv_in(Mat4* A);

#endif // MAT4_H
