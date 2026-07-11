#include "mat4.h"
#include "vec4.h"

vec4 mat4_get_row(mat4 A, unsigned int index)
{
	return VEC4(A.cols[0].data[index],
	            A.cols[1].data[index],
	            A.cols[2].data[index],
	            A.cols[3].data[index]
	);
}

mat4 mat4_add(mat4 A, mat4 B)
{
	return MAT4V(
		vec4_add(A.cols[0], B.cols[0]),
		vec4_add(A.cols[1], B.cols[1]),
		vec4_add(A.cols[2], B.cols[2]),
		vec4_add(A.cols[3], B.cols[3])
	);
}

mat4 mat4_sub(mat4 A, mat4 B)
{
	return MAT4V(
		vec4_sub(A.cols[0], B.cols[0]),
		vec4_sub(A.cols[1], B.cols[1]),
		vec4_sub(A.cols[2], B.cols[2]),
		vec4_sub(A.cols[3], B.cols[3])
	);
}

mat4 mat4_mult(mat4 A, mat4 B)
{
	mat4 At = mat4_transpose(A);

	mat4 R = MAT4_ZERO;

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

mat4 mat4_add_scal(mat4 A, float l)
{
	return MAT4V(
		vec4_add_scal(A.cols[0], l),
		vec4_add_scal(A.cols[1], l),
		vec4_add_scal(A.cols[2], l),
		vec4_add_scal(A.cols[3], l)
	);
}

mat4 mat4_sub_scal (mat4 A, float l)
{
	return MAT4V(
		vec4_sub_scal(A.cols[0], l),
		vec4_sub_scal(A.cols[1], l),
		vec4_sub_scal(A.cols[2], l),
		vec4_sub_scal(A.cols[3], l)
	);
}

mat4 mat4_mult_scal(mat4 A, float l)
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

mat4 mat4_transpose(mat4 A)
{
	return MAT4(
		A.cols[0].x, A.cols[0].y, A.cols[0].z, A.cols[0].w,
		A.cols[1].x, A.cols[1].y, A.cols[1].z, A.cols[1].w,
		A.cols[2].x, A.cols[2].y, A.cols[2].z, A.cols[2].w,
		A.cols[3].x, A.cols[3].y, A.cols[3].z, A.cols[3].w
	);
}

void mat4_add_in(mat4* A, mat4 B)
{
	vec4_add_in(&A->cols[0], B.cols[0]);
	vec4_add_in(&A->cols[1], B.cols[1]);
	vec4_add_in(&A->cols[2], B.cols[2]);
	vec4_add_in(&A->cols[3], B.cols[3]);
}

void mat4_sub_in(mat4* A, mat4 B)
{
	vec4_sub_in(&A->cols[0], B.cols[0]);
	vec4_sub_in(&A->cols[1], B.cols[1]);
	vec4_sub_in(&A->cols[2], B.cols[2]);
	vec4_sub_in(&A->cols[3], B.cols[3]);
}

void mat4_add_scal_in (mat4* A, float l)
{
	vec4_add_scal_in(&A->cols[0], l);
	vec4_add_scal_in(&A->cols[1], l);
	vec4_add_scal_in(&A->cols[2], l);
	vec4_add_scal_in(&A->cols[3], l);
}

void mat4_sub_scal_in (mat4* A, float l)
{
	vec4_sub_scal_in(&A->cols[0], l);
	vec4_sub_scal_in(&A->cols[1], l);
	vec4_sub_scal_in(&A->cols[2], l);
	vec4_sub_scal_in(&A->cols[3], l);
}

void mat4_mult_scal_in(mat4* A, float l)
{
	vec4_mult_scal_in(&A->cols[0], l);
	vec4_mult_scal_in(&A->cols[1], l);
	vec4_mult_scal_in(&A->cols[2], l);
	vec4_mult_scal_in(&A->cols[3], l);
}

// TODO !
// void mat4_inv_in(mat4* A);

