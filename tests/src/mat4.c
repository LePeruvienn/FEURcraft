#include "FEUR_Test/FEUR_Test.h"

#include "mat4.h"

FEUR_Test_Result Test_Mat4_Add()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 B = MAT4(16.f, 15.f, 14.f, 13.f,
	              12.f, 11.f, 10.f,  9.f,
	               8.f,  7.f,  6.f,  5.f,
	               4.f,  3.f,  2.f,  1.f);

	mat4 result = mat4_add(A, B);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], 17.f);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Sub()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 B = MAT4(16.f, 15.f, 14.f, 13.f,
	              12.f, 11.f, 10.f,  9.f,
	               8.f,  7.f,  6.f,  5.f,
	               4.f,  3.f,  2.f,  1.f);

	mat4 expected = MAT4(-15.f, -13.f, -11.f, -9.f,
	                       -7.f,  -5.f,  -3.f, -1.f,
	                        1.f,   3.f,   5.f,  7.f,
	                        9.f,  11.f,  13.f, 15.f);

	mat4 result = mat4_sub(A, B);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Mult()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 B = MAT4(16.f, 15.f, 14.f, 13.f,
	              12.f, 11.f, 10.f,  9.f,
	               8.f,  7.f,  6.f,  5.f,
	               4.f,  3.f,  2.f,  1.f);

	mat4 expected = MAT4( 80.f,  70.f,  60.f,  50.f,
	                      240.f, 214.f, 188.f, 162.f,
	                      400.f, 358.f, 316.f, 274.f,
	                      560.f, 502.f, 444.f, 386.f);

	mat4 result = mat4_mult(A, B);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	/* multiplying by the identity should never change the matrix */
	mat4 identity = MAT4_IDENTITY;
	mat4 unchanged = mat4_mult(A, identity);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(unchanged.data[i], A.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Add_Scal()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(11.f, 12.f, 13.f, 14.f,
	                      15.f, 16.f, 17.f, 18.f,
	                      19.f, 20.f, 21.f, 22.f,
	                      23.f, 24.f, 25.f, 26.f);

	mat4 result = mat4_add_scal(A, 10.f);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Sub_Scal()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(0.f, 1.f,  2.f,  3.f,
	                      4.f, 5.f,  6.f,  7.f,
	                      8.f, 9.f, 10.f, 11.f,
	                     12.f, 13.f, 14.f, 15.f);

	mat4 result = mat4_sub_scal(A, 1.f);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Mult_Scal()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(2.f,  4.f,  6.f,  8.f,
	                     10.f, 12.f, 14.f, 16.f,
	                     18.f, 20.f, 22.f, 24.f,
	                     26.f, 28.f, 30.f, 32.f);

	mat4 result = mat4_mult_scal(A, 2.f);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Mult_Vec4()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	vec4 u = VEC4(1.f, 1.f, 1.f, 1.f);

	/* multiplying by an all-ones vector sums each row */
	vec4 result = mat4_mult_vec4(A, u);

	FEUR_TEST_ASSERT_FLOAT(result.x, 10.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 26.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 42.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 58.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Mult_Mat4()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	vec4 u = VEC4(1.f, 1.f, 1.f, 1.f);

	/* multiplying by an all-ones vector sums each column */
	vec4 result = vec4_mult_mat4(u, A);

	FEUR_TEST_ASSERT_FLOAT(result.x, 28.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 32.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 36.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 40.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Get_Row()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	vec4 row0 = mat4_get_row(A, 0);
	vec4 row1 = mat4_get_row(A, 1);
	vec4 row2 = mat4_get_row(A, 2);
	vec4 row3 = mat4_get_row(A, 3);

	FEUR_TEST_ASSERT_FLOAT(row0.x, 1.f);
	FEUR_TEST_ASSERT_FLOAT(row0.y, 2.f);
	FEUR_TEST_ASSERT_FLOAT(row0.z, 3.f);
	FEUR_TEST_ASSERT_FLOAT(row0.w, 4.f);

	FEUR_TEST_ASSERT_FLOAT(row1.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(row1.y, 6.f);
	FEUR_TEST_ASSERT_FLOAT(row1.z, 7.f);
	FEUR_TEST_ASSERT_FLOAT(row1.w, 8.f);

	FEUR_TEST_ASSERT_FLOAT(row2.x, 9.f);
	FEUR_TEST_ASSERT_FLOAT(row2.y, 10.f);
	FEUR_TEST_ASSERT_FLOAT(row2.z, 11.f);
	FEUR_TEST_ASSERT_FLOAT(row2.w, 12.f);

	FEUR_TEST_ASSERT_FLOAT(row3.x, 13.f);
	FEUR_TEST_ASSERT_FLOAT(row3.y, 14.f);
	FEUR_TEST_ASSERT_FLOAT(row3.z, 15.f);
	FEUR_TEST_ASSERT_FLOAT(row3.w, 16.f);

	return FEUR_Test_Success;
}

/*
FEUR_Test_Result Test_Mat4_Inv()
{
	mat4 D = MAT4(2.f, 0.f, 0.f, 0.f,
	              0.f, 4.f, 0.f, 0.f,
	              0.f, 0.f, 5.f, 0.f,
	              0.f, 0.f, 0.f, 1.f);

	mat4 expected = MAT4(0.5f,  0.f,  0.f, 0.f,
	                       0.f, 0.25f, 0.f, 0.f,
	                       0.f,  0.f, 0.2f, 0.f,
	                       0.f,  0.f,  0.f, 1.f);

	mat4 result = mat4_inv(D);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	// a non-diagonal invertible matrix: 
	// check the round-trip property instead of a hand-derived inverse
	mat4 C = MAT4(1.f, 2.f, 0.f, 0.f,
	              0.f, 1.f, 3.f, 0.f,
	              0.f, 0.f, 1.f, 4.f,
	              0.f, 0.f, 0.f, 1.f);

	mat4 round_trip = mat4_mult(C, mat4_inv(C));
	mat4 identity = MAT4_IDENTITY;

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(round_trip.data[i], identity.data[i]);
	}

	return FEUR_Test_Success;
}
*/


FEUR_Test_Result Test_Mat4_Transpose()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(1.f, 5.f,  9.f, 13.f,
	                      2.f, 6.f, 10.f, 14.f,
	                      3.f, 7.f, 11.f, 15.f,
	                      4.f, 8.f, 12.f, 16.f);

	mat4 result = mat4_transpose(A);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(result.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Scale_Axes()
{
	vec4 p = VEC4(2.f, 5.f, 7.f, 1.f);

	vec4 scaled_x = mat4_mult_vec4(mat4_scale_x(3.f), p);
	vec4 scaled_y = mat4_mult_vec4(mat4_scale_y(3.f), p);
	vec4 scaled_z = mat4_mult_vec4(mat4_scale_z(3.f), p);

	FEUR_TEST_ASSERT_FLOAT(scaled_x.x, 6.f);
	FEUR_TEST_ASSERT_FLOAT(scaled_x.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(scaled_x.z, 7.f);

	FEUR_TEST_ASSERT_FLOAT(scaled_y.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(scaled_y.y, 15.f);
	FEUR_TEST_ASSERT_FLOAT(scaled_y.z, 7.f);

	FEUR_TEST_ASSERT_FLOAT(scaled_z.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(scaled_z.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(scaled_z.z, 21.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Scale()
{
	vec4 p = VEC4(2.f, 5.f, 7.f, 1.f);

	vec4 result = mat4_mult_vec4(mat4_scale(3.f), p);

	FEUR_TEST_ASSERT_FLOAT(result.x, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 15.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 21.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 1.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Translate_Axes()
{
	vec4 p = VEC4(2.f, 5.f, 7.f, 1.f);

	vec4 translated_x = mat4_mult_vec4(mat4_translate_x(3.f), p);
	vec4 translated_y = mat4_mult_vec4(mat4_translate_y(3.f), p);
	vec4 translated_z = mat4_mult_vec4(mat4_translate_z(3.f), p);

	FEUR_TEST_ASSERT_FLOAT(translated_x.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(translated_x.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(translated_x.z, 7.f);

	FEUR_TEST_ASSERT_FLOAT(translated_y.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(translated_y.y, 8.f);
	FEUR_TEST_ASSERT_FLOAT(translated_y.z, 7.f);

	FEUR_TEST_ASSERT_FLOAT(translated_z.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(translated_z.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(translated_z.z, 10.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Translate()
{
	vec4 p = VEC4(2.f, 5.f, 7.f, 1.f);
	vec3 t = VEC3(3.f, 4.f, 5.f);

	vec4 result = mat4_mult_vec4(mat4_translate(t), p);

	FEUR_TEST_ASSERT_FLOAT(result.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 9.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 12.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 1.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Rotate_Axes()
{
	float angle = 0.5f;
	mat4 identity = MAT4_IDENTITY;

	/* rotating around an axis leaves that axis unaffected */
	vec4 x_dir = VEC4(1.f, 0.f, 0.f, 0.f);
	vec4 y_dir = VEC4(0.f, 1.f, 0.f, 0.f);
	vec4 z_dir = VEC4(0.f, 0.f, 1.f, 0.f);

	vec4 rx = mat4_mult_vec4(mat4_rotate_x(angle), x_dir);
	vec4 ry = mat4_mult_vec4(mat4_rotate_y(angle), y_dir);
	vec4 rz = mat4_mult_vec4(mat4_rotate_z(angle), z_dir);

	FEUR_TEST_ASSERT_FLOAT(rx.x, x_dir.x);
	FEUR_TEST_ASSERT_FLOAT(rx.y, x_dir.y);
	FEUR_TEST_ASSERT_FLOAT(rx.z, x_dir.z);

	FEUR_TEST_ASSERT_FLOAT(ry.x, y_dir.x);
	FEUR_TEST_ASSERT_FLOAT(ry.y, y_dir.y);
	FEUR_TEST_ASSERT_FLOAT(ry.z, y_dir.z);

	FEUR_TEST_ASSERT_FLOAT(rz.x, z_dir.x);
	FEUR_TEST_ASSERT_FLOAT(rz.y, z_dir.y);
	FEUR_TEST_ASSERT_FLOAT(rz.z, z_dir.z);

	/* rotating by angle then by -angle cancels out, whatever the sign convention */
	mat4 x_roundtrip = mat4_mult(mat4_rotate_x(angle), mat4_rotate_x(-angle));
	mat4 y_roundtrip = mat4_mult(mat4_rotate_y(angle), mat4_rotate_y(-angle));
	mat4 z_roundtrip = mat4_mult(mat4_rotate_z(angle), mat4_rotate_z(-angle));

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(x_roundtrip.data[i], identity.data[i]);
	}

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(y_roundtrip.data[i], identity.data[i]);
	}

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(z_roundtrip.data[i], identity.data[i]);
	}

	return FEUR_Test_Success;
}


/*
FEUR_Test_Result Test_Mat4_Rotate()
{
	vec3 axis = VEC3(0.57735f, 0.57735f, 0.57735f);
	float angle = 0.5f;

	mat4 R = mat4_rotate(axis, angle);

	// a vector along the rotation axis is unaffected by the rotation
	vec4 axis_dir = VEC4(axis.x, axis.y, axis.z, 0.f);
	vec4 rotated_axis = mat4_mult_vec4(R, axis_dir);

	FEUR_TEST_ASSERT_FLOAT(rotated_axis.x, axis_dir.x);
	FEUR_TEST_ASSERT_FLOAT(rotated_axis.y, axis_dir.y);
	FEUR_TEST_ASSERT_FLOAT(rotated_axis.z, axis_dir.z);

	// rotation preserves length for any vector
	vec4 v = VEC4(1.f, -1.f, 0.f, 0.f);
	vec4 rotated_v = mat4_mult_vec4(R, v);

	FEUR_TEST_ASSERT_FLOAT(vec4_len2(rotated_v), vec4_len2(v));

	// rotating by 0 does nothing
	mat4 no_rotation = mat4_rotate(axis, 0.f);
	mat4 identity = MAT4_IDENTITY;

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(no_rotation.data[i], identity.data[i]);
	}

	return FEUR_Test_Success;
}
*/


FEUR_Test_Result Test_Mat4_Add_In()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 B = MAT4(16.f, 15.f, 14.f, 13.f,
	              12.f, 11.f, 10.f,  9.f,
	               8.f,  7.f,  6.f,  5.f,
	               4.f,  3.f,  2.f,  1.f);

	mat4_add_in(&A, B);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(A.data[i], 17.f);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Sub_In()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 B = MAT4(16.f, 15.f, 14.f, 13.f,
	              12.f, 11.f, 10.f,  9.f,
	               8.f,  7.f,  6.f,  5.f,
	               4.f,  3.f,  2.f,  1.f);

	mat4 expected = MAT4(-15.f, -13.f, -11.f, -9.f,
	                       -7.f,  -5.f,  -3.f, -1.f,
	                        1.f,   3.f,   5.f,  7.f,
	                        9.f,  11.f,  13.f, 15.f);

	mat4_sub_in(&A, B);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(A.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Add_Scal_In()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(11.f, 12.f, 13.f, 14.f,
	                      15.f, 16.f, 17.f, 18.f,
	                      19.f, 20.f, 21.f, 22.f,
	                      23.f, 24.f, 25.f, 26.f);

	mat4_add_scal_in(&A, 10.f);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(A.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Sub_Scal_In()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(0.f, 1.f,  2.f,  3.f,
	                      4.f, 5.f,  6.f,  7.f,
	                      8.f, 9.f, 10.f, 11.f,
	                     12.f, 13.f, 14.f, 15.f);

	mat4_sub_scal_in(&A, 1.f);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(A.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Mat4_Mult_Scal_In()
{
	mat4 A = MAT4(1.f,  2.f,  3.f,  4.f,
	              5.f,  6.f,  7.f,  8.f,
	              9.f, 10.f, 11.f, 12.f,
	             13.f, 14.f, 15.f, 16.f);

	mat4 expected = MAT4(2.f,  4.f,  6.f,  8.f,
	                     10.f, 12.f, 14.f, 16.f,
	                     18.f, 20.f, 22.f, 24.f,
	                     26.f, 28.f, 30.f, 32.f);

	mat4_mult_scal_in(&A, 2.f);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(A.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}


/*
FEUR_Test_Result Test_Mat4_Inv_In()
{
	mat4 D = MAT4(2.f, 0.f, 0.f, 0.f,
	              0.f, 4.f, 0.f, 0.f,
	              0.f, 0.f, 5.f, 0.f,
	              0.f, 0.f, 0.f, 1.f);

	mat4 expected = MAT4(0.5f,  0.f,  0.f, 0.f,
	                       0.f, 0.25f, 0.f, 0.f,
	                       0.f,  0.f, 0.2f, 0.f,
	                       0.f,  0.f,  0.f, 1.f);

	mat4_inv_in(&D);

	for(int i = 0; i < 16; ++i)
	{
		FEUR_TEST_ASSERT_FLOAT(D.data[i], expected.data[i]);
	}

	return FEUR_Test_Success;
}
*/


int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Running mat4 unit tests...");

	FEUR_Test_Add_Group("Matrix Arithmetic");

	FEUR_Test_Add_Test("Add", Test_Mat4_Add);
	FEUR_Test_Add_Test("Sub", Test_Mat4_Sub);
	FEUR_Test_Add_Test("Mult", Test_Mat4_Mult);
	FEUR_Test_Add_Test("Add Scalar", Test_Mat4_Add_Scal);
	FEUR_Test_Add_Test("Sub Scalar", Test_Mat4_Sub_Scal);
	FEUR_Test_Add_Test("Mult Scalar", Test_Mat4_Mult_Scal);

	FEUR_Test_Add_Group("Vector Multiplication & Rows");

	FEUR_Test_Add_Test("Mat4 * Vec4", Test_Mat4_Mult_Vec4);
	FEUR_Test_Add_Test("Vec4 * Mat4", Test_Vec4_Mult_Mat4);
	FEUR_Test_Add_Test("Get Row", Test_Mat4_Get_Row);

	FEUR_Test_Add_Group("Inverse & Transpose");

	// FEUR_Test_Add_Test("Inverse", Test_Mat4_Inv);
	FEUR_Test_Add_Test("Transpose", Test_Mat4_Transpose);

	FEUR_Test_Add_Group("Transform Construction");

	FEUR_Test_Add_Test("Scale Axes", Test_Mat4_Scale_Axes);
	FEUR_Test_Add_Test("Scale", Test_Mat4_Scale);
	FEUR_Test_Add_Test("Translate Axes", Test_Mat4_Translate_Axes);
	FEUR_Test_Add_Test("Translate", Test_Mat4_Translate);

	FEUR_Test_Add_Group("Rotation Transforms");

	FEUR_Test_Add_Test("Rotate Axes", Test_Mat4_Rotate_Axes);
	// FEUR_Test_Add_Test("Rotate", Test_Mat4_Rotate);

	FEUR_Test_Add_Group("In-Place Operations");

	FEUR_Test_Add_Test("Add In", Test_Mat4_Add_In);
	FEUR_Test_Add_Test("Sub In", Test_Mat4_Sub_In);
	FEUR_Test_Add_Test("Add Scalar In", Test_Mat4_Add_Scal_In);
	FEUR_Test_Add_Test("Sub Scalar In", Test_Mat4_Sub_Scal_In);
	FEUR_Test_Add_Test("Mult Scalar In", Test_Mat4_Mult_Scal_In);
	// FEUR_Test_Add_Test("Inverse In", Test_Mat4_Inv_In);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
