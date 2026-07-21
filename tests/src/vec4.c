#include "FEUR_Test/FEUR_Test.h"

#include "vec4.h"

FEUR_Test_Result Test_Vec4_Add()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);
	Vec4 v = VEC4(5.f, 6.f, 7.f, 8.f);

	Vec4 result = vec4_add(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 8.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 10.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 12.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Sub()
{
	Vec4 u = VEC4(6.f, 8.f, 10.f, 12.f);
	Vec4 v = VEC4(1.f, 2.f, 3.f, 4.f);

	Vec4 result = vec4_sub(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 7.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 8.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Add_Scal()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);

	Vec4 result = vec4_add_scal(u, 1.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 3.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 4.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Sub_Scal()
{
	Vec4 u = VEC4(5.f, 6.f, 7.f, 8.f);

	Vec4 result = vec4_sub_scal(u, 1.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 7.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Mult_Scal()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);

	Vec4 result = vec4_mult_scal(u, 2.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 4.f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 6.f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 8.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Add_In()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);
	Vec4 v = VEC4(5.f, 6.f, 7.f, 8.f);

	vec4_add_in(&u, v);

	FEUR_TEST_ASSERT_FLOAT(u.x, 6.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 8.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 10.f);
	FEUR_TEST_ASSERT_FLOAT(u.w, 12.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Sub_In()
{
	Vec4 u = VEC4(6.f, 8.f, 10.f, 12.f);
	Vec4 v = VEC4(1.f, 2.f, 3.f, 4.f);

	vec4_sub_in(&u, v);

	FEUR_TEST_ASSERT_FLOAT(u.x, 5.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 6.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 7.f);
	FEUR_TEST_ASSERT_FLOAT(u.w, 8.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Add_Scal_In()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);

	vec4_add_scal_in(&u, 1.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 3.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 4.f);
	FEUR_TEST_ASSERT_FLOAT(u.w, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Sub_Scal_In()
{
	Vec4 u = VEC4(5.f, 6.f, 7.f, 8.f);

	vec4_sub_scal_in(&u, 1.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 5.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 6.f);
	FEUR_TEST_ASSERT_FLOAT(u.w, 7.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Mult_Scal_In()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);

	vec4_mult_scal_in(&u, 2.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 2.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 4.f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 6.f);
	FEUR_TEST_ASSERT_FLOAT(u.w, 8.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Dot()
{
	Vec4 u = VEC4(1.f, 2.f, 3.f, 4.f);
	Vec4 v = VEC4(5.f, 6.f, 7.f, 8.f);

	float result = vec4_dot(u, v);

	FEUR_TEST_ASSERT_FLOAT(result, 70.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Len()
{
	Vec4 u = VEC4(1.f, 2.f, 2.f, 4.f);

	FEUR_TEST_ASSERT_FLOAT(vec4_len(u), 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Len2()
{
	Vec4 u = VEC4(1.f, 2.f, 2.f, 4.f);

	FEUR_TEST_ASSERT_FLOAT(vec4_len2(u), 25.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Dist()
{
	Vec4 u = VEC4(1.f, 1.f, 1.f, 1.f);
	Vec4 v = VEC4(2.f, 3.f, 3.f, 5.f);

	FEUR_TEST_ASSERT_FLOAT(vec4_dist(u, v), 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Dist2()
{
	Vec4 u = VEC4(1.f, 1.f, 1.f, 1.f);
	Vec4 v = VEC4(2.f, 3.f, 3.f, 5.f);

	FEUR_TEST_ASSERT_FLOAT(vec4_dist2(u, v), 25.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Norm()
{
	Vec4 u = VEC4(1.f, 2.f, 2.f, 4.f);

	Vec4 result = vec4_norm(u);

	FEUR_TEST_ASSERT_FLOAT(result.x, 0.2f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 0.4f);
	FEUR_TEST_ASSERT_FLOAT(result.z, 0.4f);
	FEUR_TEST_ASSERT_FLOAT(result.w, 0.8f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec4_Norm_In()
{
	Vec4 u = VEC4(1.f, 2.f, 2.f, 4.f);

	vec4_norm_in(&u);

	FEUR_TEST_ASSERT_FLOAT(u.x, 0.2f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 0.4f);
	FEUR_TEST_ASSERT_FLOAT(u.z, 0.4f);
	FEUR_TEST_ASSERT_FLOAT(u.w, 0.8f);

	return FEUR_Test_Success;
}


int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Running vec4 unit tests...");

	FEUR_Test_Add_Group("Arithmetic");

	FEUR_Test_Add_Test("Add", Test_Vec4_Add);
	FEUR_Test_Add_Test("Sub", Test_Vec4_Sub);
	FEUR_Test_Add_Test("Add Scalar", Test_Vec4_Add_Scal);
	FEUR_Test_Add_Test("Sub Scalar", Test_Vec4_Sub_Scal);
	FEUR_Test_Add_Test("Mult Scalar", Test_Vec4_Mult_Scal);

	FEUR_Test_Add_Group("In-Place Arithmetic");

	FEUR_Test_Add_Test("Add In", Test_Vec4_Add_In);
	FEUR_Test_Add_Test("Sub In", Test_Vec4_Sub_In);
	FEUR_Test_Add_Test("Add Scalar In", Test_Vec4_Add_Scal_In);
	FEUR_Test_Add_Test("Sub Scalar In", Test_Vec4_Sub_Scal_In);
	FEUR_Test_Add_Test("Mult Scalar In", Test_Vec4_Mult_Scal_In);

	FEUR_Test_Add_Group("Products & Metrics");

	FEUR_Test_Add_Test("Dot", Test_Vec4_Dot);
	FEUR_Test_Add_Test("Len", Test_Vec4_Len);
	FEUR_Test_Add_Test("Len2", Test_Vec4_Len2);
	FEUR_Test_Add_Test("Dist", Test_Vec4_Dist);
	FEUR_Test_Add_Test("Dist2", Test_Vec4_Dist2);

	FEUR_Test_Add_Group("Normalization");

	FEUR_Test_Add_Test("Norm", Test_Vec4_Norm);
	FEUR_Test_Add_Test("Norm In", Test_Vec4_Norm_In);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
