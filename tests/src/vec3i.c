#include "FEUR_Test/FEUR_Test.h"

#include "vec3i.h"

FEUR_Test_Result Test_Vec3i_Create()
{
	Vec3i v = VEC3I(1, 2, 3);

	FEUR_TEST_ASSERT_EQUAL(v.x, 1);
	FEUR_TEST_ASSERT_EQUAL(v.y, 2);
	FEUR_TEST_ASSERT_EQUAL(v.z, 3);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Zero()
{
	Vec3i v = VEC3I_ZERO;

	FEUR_TEST_ASSERT_EQUAL(v.x, 0);
	FEUR_TEST_ASSERT_EQUAL(v.y, 0);
	FEUR_TEST_ASSERT_EQUAL(v.z, 0);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_One()
{
	Vec3i v = VEC3I_ONE;

	FEUR_TEST_ASSERT_EQUAL(v.x, 1);
	FEUR_TEST_ASSERT_EQUAL(v.y, 1);
	FEUR_TEST_ASSERT_EQUAL(v.z, 1);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Add()
{
	Vec3i u = VEC3I(1, 2, 3);
	Vec3i v = VEC3I(4, 5, 6);

	Vec3i result = vec3i_add(u, v);

	FEUR_TEST_ASSERT_EQUAL(result.x, 5);
	FEUR_TEST_ASSERT_EQUAL(result.y, 7);
	FEUR_TEST_ASSERT_EQUAL(result.z, 9);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Sub()
{
	Vec3i u = VEC3I(9, 8, 7);
	Vec3i v = VEC3I(4, 3, 2);

	Vec3i result = vec3i_sub(u, v);

	FEUR_TEST_ASSERT_EQUAL(result.x, 5);
	FEUR_TEST_ASSERT_EQUAL(result.y, 5);
	FEUR_TEST_ASSERT_EQUAL(result.z, 5);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Add_Scal()
{
	Vec3i u = VEC3I(1, 2, 3);

	Vec3i result = vec3i_add_scal(u, 5);

	FEUR_TEST_ASSERT_EQUAL(result.x, 6);
	FEUR_TEST_ASSERT_EQUAL(result.y, 7);
	FEUR_TEST_ASSERT_EQUAL(result.z, 8);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Sub_Scal()
{
	Vec3i u = VEC3I(9, 8, 7);

	Vec3i result = vec3i_sub_scal(u, 2);

	FEUR_TEST_ASSERT_EQUAL(result.x, 7);
	FEUR_TEST_ASSERT_EQUAL(result.y, 6);
	FEUR_TEST_ASSERT_EQUAL(result.z, 5);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Mult_Scal()
{
	Vec3i u = VEC3I(1, 2, 3);

	Vec3i result = vec3i_mult_scal(u, 4);

	FEUR_TEST_ASSERT_EQUAL(result.x, 4);
	FEUR_TEST_ASSERT_EQUAL(result.y, 8);
	FEUR_TEST_ASSERT_EQUAL(result.z, 12);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Add_In()
{
	Vec3i u = VEC3I(1, 2, 3);
	Vec3i v = VEC3I(4, 5, 6);

	vec3i_add_in(&u, v);

	FEUR_TEST_ASSERT_EQUAL(u.x, 5);
	FEUR_TEST_ASSERT_EQUAL(u.y, 7);
	FEUR_TEST_ASSERT_EQUAL(u.z, 9);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Sub_In()
{
	Vec3i u = VEC3I(9, 8, 7);
	Vec3i v = VEC3I(4, 3, 2);

	vec3i_sub_in(&u, v);

	FEUR_TEST_ASSERT_EQUAL(u.x, 5);
	FEUR_TEST_ASSERT_EQUAL(u.y, 5);
	FEUR_TEST_ASSERT_EQUAL(u.z, 5);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Add_Scal_In()
{
	Vec3i u = VEC3I(1, 2, 3);

	vec3i_add_scal_in(&u, 5);

	FEUR_TEST_ASSERT_EQUAL(u.x, 6);
	FEUR_TEST_ASSERT_EQUAL(u.y, 7);
	FEUR_TEST_ASSERT_EQUAL(u.z, 8);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Sub_Scal_In()
{
	Vec3i u = VEC3I(9, 8, 7);

	vec3i_sub_scal_in(&u, 2);

	FEUR_TEST_ASSERT_EQUAL(u.x, 7);
	FEUR_TEST_ASSERT_EQUAL(u.y, 6);
	FEUR_TEST_ASSERT_EQUAL(u.z, 5);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Mult_Scal_In()
{
	Vec3i u = VEC3I(1, 2, 3);

	vec3i_mult_scal_in(&u, 4);

	FEUR_TEST_ASSERT_EQUAL(u.x, 4);
	FEUR_TEST_ASSERT_EQUAL(u.y, 8);
	FEUR_TEST_ASSERT_EQUAL(u.z, 12);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Cross()
{
	Vec3i x_axis = VEC3I(1, 0, 0);
	Vec3i y_axis = VEC3I(0, 1, 0);

	Vec3i basis = vec3i_cross(x_axis, y_axis);

	FEUR_TEST_ASSERT_EQUAL(basis.x, 0);
	FEUR_TEST_ASSERT_EQUAL(basis.y, 0);
	FEUR_TEST_ASSERT_EQUAL(basis.z, 1);

	Vec3i u = VEC3I(1, 2, 3);
	Vec3i v = VEC3I(4, 5, 6);

	Vec3i result = vec3i_cross(u, v);

	FEUR_TEST_ASSERT_EQUAL(result.x, -3);
	FEUR_TEST_ASSERT_EQUAL(result.y, 6);
	FEUR_TEST_ASSERT_EQUAL(result.z, -3);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Len()
{
	Vec3i u = VEC3I(1, 2, 2);

	FEUR_TEST_ASSERT_FLOAT(vec3i_len(u), 3.f);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Len2()
{
	Vec3i u = VEC3I(1, 2, 2);

	FEUR_TEST_ASSERT_EQUAL(vec3i_len2(u), 9);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Dist()
{
	Vec3i u = VEC3I(1, 1, 1);
	Vec3i v = VEC3I(2, 3, 3);

	FEUR_TEST_ASSERT_FLOAT(vec3i_dist(u, v), 3.f);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Vec3i_Dist2()
{
	Vec3i u = VEC3I(1, 1, 1);
	Vec3i v = VEC3I(2, 3, 3);

	FEUR_TEST_ASSERT_FLOAT(vec3i_dist2(u, v), 9.f);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Running Vec3i unit tests...");

	FEUR_Test_Add_Group("Construction");

	FEUR_Test_Add_Test("Create", Test_Vec3i_Create);
	FEUR_Test_Add_Test("Zero", Test_Vec3i_Zero);
	FEUR_Test_Add_Test("One", Test_Vec3i_One);

	FEUR_Test_Add_Group("Arithmetic");

	FEUR_Test_Add_Test("Add", Test_Vec3i_Add);
	FEUR_Test_Add_Test("Sub", Test_Vec3i_Sub);
	FEUR_Test_Add_Test("Add Scalar", Test_Vec3i_Add_Scal);
	FEUR_Test_Add_Test("Sub Scalar", Test_Vec3i_Sub_Scal);
	FEUR_Test_Add_Test("Mult Scalar", Test_Vec3i_Mult_Scal);

	FEUR_Test_Add_Group("In-Place Arithmetic");

	FEUR_Test_Add_Test("Add In", Test_Vec3i_Add_In);
	FEUR_Test_Add_Test("Sub In", Test_Vec3i_Sub_In);
	FEUR_Test_Add_Test("Add Scalar In", Test_Vec3i_Add_Scal_In);
	FEUR_Test_Add_Test("Sub Scalar In", Test_Vec3i_Sub_Scal_In);
	FEUR_Test_Add_Test("Mult Scalar In", Test_Vec3i_Mult_Scal_In);

	FEUR_Test_Add_Group("Metrics");

	FEUR_Test_Add_Test("Cross", Test_Vec3i_Cross);
	FEUR_Test_Add_Test("Len", Test_Vec3i_Len);
	FEUR_Test_Add_Test("Len2", Test_Vec3i_Len2);
	FEUR_Test_Add_Test("Dist", Test_Vec3i_Dist);
	FEUR_Test_Add_Test("Dist2", Test_Vec3i_Dist2);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
