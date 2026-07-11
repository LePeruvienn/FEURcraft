#include "FEUR_Test/FEUR_Test.h"

#include "vec3.h"

FEUR_Test_Result Test_Vec3_Add()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);
	vec3 v = VEC3(4.f, 5.f, 6.f);

	vec3 result = vec3_add(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 7.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 9.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Sub()
{
	vec3 u = VEC3(9.f, 8.f, 7.f);
	vec3 v = VEC3(4.f, 3.f, 2.f);

	vec3 result = vec3_sub(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Add_Scal()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);

	vec3 result = vec3_add_scal(u, 5.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 7.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 8.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Sub_Scal()
{
	vec3 u = VEC3(9.f, 8.f, 7.f);

	vec3 result = vec3_sub_scal(u, 2.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 7.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Mult_Scal()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);

	vec3 result = vec3_mult_scal(u, 4.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 8.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 12.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Add_In()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);
	vec3 v = VEC3(4.f, 5.f, 6.f);

	vec3_add_in(&u, v);

	FEUR_TEST_ASSERT_FLOAT(u.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 7.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 9.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Sub_In()
{
	vec3 u = VEC3(9.f, 8.f, 7.f);
	vec3 v = VEC3(4.f, 3.f, 2.f);

	vec3_sub_in(&u, v);

	FEUR_TEST_ASSERT_FLOAT(u.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Add_Scal_In()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);

	vec3_add_scal_in(&u, 5.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 6.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 7.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 8.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Sub_Scal_In()
{
	vec3 u = VEC3(9.f, 8.f, 7.f);

	vec3_sub_scal_in(&u, 2.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 7.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 6.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Mult_Scal_In()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);

	vec3_mult_scal_in(&u, 4.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 8.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 12.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Dot()
{
	vec3 u = VEC3(1.f, 2.f, 3.f);
	vec3 v = VEC3(4.f, 5.f, 6.f);

	float result = vec3_dot(u, v);

	FEUR_TEST_ASSERT_FLOAT(result, 32.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Cross()
{
	vec3 x_axis = VEC3(1.f, 0.f, 0.f);
	vec3 y_axis = VEC3(0.f, 1.f, 0.f);

	vec3 basis_result = vec3_cross(x_axis, y_axis);

	FEUR_TEST_ASSERT_FLOAT(basis_result.x, 0.f);
	FEUR_TEST_ASSERT_FLOAT(basis_result.y, 0.f);
	FEUR_TEST_ASSERT_FLOAT(basis_result.z, 1.f);

	vec3 u = VEC3(1.f, 2.f, 3.f);
	vec3 v = VEC3(4.f, 5.f, 6.f);

	vec3 result = vec3_cross(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, -3.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, -3.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Len()
{
	vec3 u = VEC3(1.f, 2.f, 2.f);

	FEUR_TEST_ASSERT_FLOAT(vec3_len(u), 3.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Len2()
{
	vec3 u = VEC3(1.f, 2.f, 2.f);

	FEUR_TEST_ASSERT_FLOAT(vec3_len2(u), 9.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Dist()
{
	vec3 u = VEC3(1.f, 1.f, 1.f);
	vec3 v = VEC3(2.f, 3.f, 3.f);

	FEUR_TEST_ASSERT_FLOAT(vec3_dist(u, v), 3.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Dist2()
{
	vec3 u = VEC3(1.f, 1.f, 1.f);
	vec3 v = VEC3(2.f, 3.f, 3.f);

	FEUR_TEST_ASSERT_FLOAT(vec3_dist2(u, v), 9.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Norm()
{
	vec3 u = VEC3(1.f, 2.f, 2.f);

	vec3 result = vec3_norm(u);

	FEUR_TEST_ASSERT_FLOAT(result.x, 0.333333f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 0.666667f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 0.666667f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec3_Norm_In()
{
	vec3 u = VEC3(1.f, 2.f, 2.f);

	vec3_norm_in(&u);

	FEUR_TEST_ASSERT_FLOAT(u.x, 0.333333f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 0.666667f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 0.666667f);

	return FEUR_Test_Success;
}


int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Running vec3 unit tests...");

	FEUR_Test_Add_Group("Arithmetic");

	FEUR_Test_Add_Test("Add", Test_Vec3_Add);
	FEUR_Test_Add_Test("Sub", Test_Vec3_Sub);
	FEUR_Test_Add_Test("Add Scalar", Test_Vec3_Add_Scal);
	FEUR_Test_Add_Test("Sub Scalar", Test_Vec3_Sub_Scal);
	FEUR_Test_Add_Test("Mult Scalar", Test_Vec3_Mult_Scal);

	FEUR_Test_Add_Group("In-Place Arithmetic");

	FEUR_Test_Add_Test("Add In", Test_Vec3_Add_In);
	FEUR_Test_Add_Test("Sub In", Test_Vec3_Sub_In);
	FEUR_Test_Add_Test("Add Scalar In", Test_Vec3_Add_Scal_In);
	FEUR_Test_Add_Test("Sub Scalar In", Test_Vec3_Sub_Scal_In);
	FEUR_Test_Add_Test("Mult Scalar In", Test_Vec3_Mult_Scal_In);

	FEUR_Test_Add_Group("Products & Metrics");

	FEUR_Test_Add_Test("Dot", Test_Vec3_Dot);
	FEUR_Test_Add_Test("Cross", Test_Vec3_Cross);
	FEUR_Test_Add_Test("Len", Test_Vec3_Len);
	FEUR_Test_Add_Test("Len2", Test_Vec3_Len2);
	FEUR_Test_Add_Test("Dist", Test_Vec3_Dist);
	FEUR_Test_Add_Test("Dist2", Test_Vec3_Dist2);

	FEUR_Test_Add_Group("Normalization");

	FEUR_Test_Add_Test("Norm", Test_Vec3_Norm);
	FEUR_Test_Add_Test("Norm In", Test_Vec3_Norm_In);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
