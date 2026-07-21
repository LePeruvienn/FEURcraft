#include "mat4.h"
#include "vec4.h"

#include <math.h>

Vec4 vec4_mult_mat4(Vec4 u, Mat4 A)
{
	return VEC4(
		vec4_dot(A.cols[0], u),
		vec4_dot(A.cols[1], u),
		vec4_dot(A.cols[2], u),
		vec4_dot(A.cols[3], u)
	);
}


Vec4 mat4_mult_vec4(Mat4 A, Vec4 u)
{
	Mat4 At = mat4_transpose(A);

	return VEC4(
		vec4_dot(At.cols[0], u),
		vec4_dot(At.cols[1], u),
		vec4_dot(At.cols[2], u),
		vec4_dot(At.cols[3], u)
	);
}

Vec4 mat4_get_row(Mat4 A, unsigned int index)
{
	return VEC4(A.cols[0].data[index],
	            A.cols[1].data[index],
	            A.cols[2].data[index],
	            A.cols[3].data[index]
	);
}

Mat4 mat4_add(Mat4 A, Mat4 B)
{
	return MAT4V(
		vec4_add(A.cols[0], B.cols[0]),
		vec4_add(A.cols[1], B.cols[1]),
		vec4_add(A.cols[2], B.cols[2]),
		vec4_add(A.cols[3], B.cols[3])
	);
}

Mat4 mat4_sub(Mat4 A, Mat4 B)
{
	return MAT4V(
		vec4_sub(A.cols[0], B.cols[0]),
		vec4_sub(A.cols[1], B.cols[1]),
		vec4_sub(A.cols[2], B.cols[2]),
		vec4_sub(A.cols[3], B.cols[3])
	);
}

Mat4 mat4_mult(Mat4 A, Mat4 B)
{
	Mat4 At = mat4_transpose(A);

	Mat4 R = MAT4_ZERO;

	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			float v_ij = vec4_dot(At.cols[j], B.cols[i]);
			R.cols[i].data[j] = v_ij;
		}
	}

	return R;
}

Mat4 mat4_add_scal(Mat4 A, float l)
{
	return MAT4V(
		vec4_add_scal(A.cols[0], l),
		vec4_add_scal(A.cols[1], l),
		vec4_add_scal(A.cols[2], l),
		vec4_add_scal(A.cols[3], l)
	);
}

Mat4 mat4_sub_scal (Mat4 A, float l)
{
	return MAT4V(
		vec4_sub_scal(A.cols[0], l),
		vec4_sub_scal(A.cols[1], l),
		vec4_sub_scal(A.cols[2], l),
		vec4_sub_scal(A.cols[3], l)
	);
}

Mat4 mat4_mult_scal(Mat4 A, float l)
{
	return MAT4V(
		vec4_mult_scal(A.cols[0], l),
		vec4_mult_scal(A.cols[1], l),
		vec4_mult_scal(A.cols[2], l),
		vec4_mult_scal(A.cols[3], l)
	);
}

// TODO !
// mat4 mat4_inv(mat4 A);

Mat4 mat4_transpose(Mat4 A)
{
	return MAT4(
		A.cols[0].x, A.cols[0].y, A.cols[0].z, A.cols[0].w,
		A.cols[1].x, A.cols[1].y, A.cols[1].z, A.cols[1].w,
		A.cols[2].x, A.cols[2].y, A.cols[2].z, A.cols[2].w,
		A.cols[3].x, A.cols[3].y, A.cols[3].z, A.cols[3].w
	);
}


Mat4 mat4_scale_x(float s)
{
	return MAT4(  s, 0.f, 0.f, 0.f,
	            0.f, 1.f, 0.f, 0.f,
	            0.f, 0.f, 1.f, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_scale_y(float s)
{
	return MAT4(1.f, 0.f, 0.f, 0.f,
	            0.f,   s, 0.f, 0.f,
	            0.f, 0.f, 1.f, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_scale_z(float s)
{
	return MAT4(1.f, 0.f, 0.f, 0.f,
	            0.f, 1.f, 0.f, 0.f,
	            0.f, 0.f,   s, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_scale(float s)
{
	return MAT4(  s, 0.f, 0.f, 0.f,
	            0.f,   s, 0.f, 0.f,
	            0.f, 0.f,   s, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_translate_x(float t)
{
	return MAT4(1.f, 0.f, 0.f,   t,
	            0.f, 1.f, 0.f, 0.f,
	            0.f, 0.f, 1.f, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_translate_y(float t)
{
	return MAT4(1.f, 0.f, 0.f, 0.f,
	            0.f, 1.f, 0.f,   t,
	            0.f, 0.f, 1.f, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_translate_z(float t)
{
	return MAT4(1.f, 0.f, 0.f, 0.f,
	            0.f, 1.f, 0.f, 0.f,
	            0.f, 0.f, 1.f,   t,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_translate(Vec3 t)
{
	return MAT4(1.f, 0.f, 0.f, t.x,
	            0.f, 1.f, 0.f, t.y,
	            0.f, 0.f, 1.f, t.z,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_rotate_x(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	return MAT4(1.f, 0.f, 0.f, 0.f,
	            0.f,   c,  -s, 0.f,
	            0.f,   s,   c, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_rotate_y(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	return MAT4(  c, 0.f,   s, 0.f,
	            0.f, 1.f, 0.f, 0.f,
	             -s, 0.f,   c, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

Mat4 mat4_rotate_z(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	return MAT4(  c,  -s, 0.f, 0.f,
	              s,   c, 0.f, 0.f,
	            0.f, 0.f, 1.f, 0.f,
	            0.f, 0.f, 0.f, 1.f);
}

// TODO !
Mat4 mat4_rotate(Vec3 axis, float angle);

void mat4_add_in(Mat4* A, Mat4 B)
{
	vec4_add_in(&A->cols[0], B.cols[0]);
	vec4_add_in(&A->cols[1], B.cols[1]);
	vec4_add_in(&A->cols[2], B.cols[2]);
	vec4_add_in(&A->cols[3], B.cols[3]);
}

void mat4_sub_in(Mat4* A, Mat4 B)
{
	vec4_sub_in(&A->cols[0], B.cols[0]);
	vec4_sub_in(&A->cols[1], B.cols[1]);
	vec4_sub_in(&A->cols[2], B.cols[2]);
	vec4_sub_in(&A->cols[3], B.cols[3]);
}

void mat4_add_scal_in (Mat4* A, float l)
{
	vec4_add_scal_in(&A->cols[0], l);
	vec4_add_scal_in(&A->cols[1], l);
	vec4_add_scal_in(&A->cols[2], l);
	vec4_add_scal_in(&A->cols[3], l);
}

void mat4_sub_scal_in (Mat4* A, float l)
{
	vec4_sub_scal_in(&A->cols[0], l);
	vec4_sub_scal_in(&A->cols[1], l);
	vec4_sub_scal_in(&A->cols[2], l);
	vec4_sub_scal_in(&A->cols[3], l);
}

void mat4_mult_scal_in(Mat4* A, float l)
{
	vec4_mult_scal_in(&A->cols[0], l);
	vec4_mult_scal_in(&A->cols[1], l);
	vec4_mult_scal_in(&A->cols[2], l);
	vec4_mult_scal_in(&A->cols[3], l);
}

// TODO !
// void mat4_inv_in(mat4* A);

