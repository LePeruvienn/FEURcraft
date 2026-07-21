#include "FEUR_Test/FEUR_Test.h"

#include "vec2.h"

FEUR_Test_Result Test_Vec2_Add()
{
	Vec2 u = VEC2(1.f, 2.f);
	Vec2 v = VEC2(3.f, 4.f);

	Vec2 result = vec2_add(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 6.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Sub()
{
	Vec2 u = VEC2(5.f, 7.f);
	Vec2 v = VEC2(2.f, 3.f);

	Vec2 result = vec2_sub(u, v);

	FEUR_TEST_ASSERT_FLOAT(result.x, 3.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 4.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Add_Scal()
{
	Vec2 u = VEC2(1.f, 2.f);

	Vec2 result = vec2_add_scal(u, 3.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Sub_Scal()
{
	Vec2 u = VEC2(5.f, 7.f);

	Vec2 result = vec2_sub_scal(u, 2.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 3.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Mult_Scal()
{
	Vec2 u = VEC2(2.f, 3.f);

	Vec2 result = vec2_mult_scal(u, 4.f);

	FEUR_TEST_ASSERT_FLOAT(result.x, 8.f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 12.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Add_In()
{
	Vec2 u = VEC2(1.f, 2.f);
	Vec2 v = VEC2(3.f, 4.f);

	vec2_add_in(&u, v);

	FEUR_TEST_ASSERT_FLOAT(u.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 6.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Sub_In()
{
	Vec2 u = VEC2(5.f, 7.f);
	Vec2 v = VEC2(2.f, 3.f);

	vec2_sub_in(&u, v);

	FEUR_TEST_ASSERT_FLOAT(u.x, 3.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 4.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Add_Scal_In()
{
	Vec2 u = VEC2(1.f, 2.f);

	vec2_add_scal_in(&u, 3.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 4.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Sub_Scal_In()
{
	Vec2 u = VEC2(5.f, 7.f);

	vec2_sub_scal_in(&u, 2.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 3.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Mult_Scal_In()
{
	Vec2 u = VEC2(2.f, 3.f);

	vec2_mult_scal_in(&u, 4.f);

	FEUR_TEST_ASSERT_FLOAT(u.x, 8.f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 12.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Dot()
{
	Vec2 u = VEC2(1.f, 2.f);
	Vec2 v = VEC2(3.f, 4.f);

	float result = vec2_dot(u, v);

	FEUR_TEST_ASSERT_FLOAT(result, 11.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Len()
{
	Vec2 u = VEC2(3.f, 4.f);

	FEUR_TEST_ASSERT_FLOAT(vec2_len(u), 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Len2()
{
	Vec2 u = VEC2(3.f, 4.f);

	FEUR_TEST_ASSERT_FLOAT(vec2_len2(u), 25.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Dist()
{
	Vec2 u = VEC2(1.f, 1.f);
	Vec2 v = VEC2(4.f, 5.f);

	FEUR_TEST_ASSERT_FLOAT(vec2_dist(u, v), 5.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Dist2()
{
	Vec2 u = VEC2(1.f, 1.f);
	Vec2 v = VEC2(4.f, 5.f);

	FEUR_TEST_ASSERT_FLOAT(vec2_dist2(u, v), 25.f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Norm()
{
	Vec2 u = VEC2(3.f, 4.f);

	Vec2 result = vec2_norm(u);

	FEUR_TEST_ASSERT_FLOAT(result.x, 0.6f);
	FEUR_TEST_ASSERT_FLOAT(result.y, 0.8f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Vec2_Norm_In()
{
	Vec2 u = VEC2(3.f, 4.f);

	vec2_norm_in(&u);

	FEUR_TEST_ASSERT_FLOAT(u.x, 0.6f);
	FEUR_TEST_ASSERT_FLOAT(u.y, 0.8f);

	return FEUR_Test_Success;
}


int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Running vec2 unit tests...");

	FEUR_Test_Add_Group("Arithmetic");

	FEUR_Test_Add_Test("Add", Test_Vec2_Add);
	FEUR_Test_Add_Test("Sub", Test_Vec2_Sub);
	FEUR_Test_Add_Test("Add Scalar", Test_Vec2_Add_Scal);
	FEUR_Test_Add_Test("Sub Scalar", Test_Vec2_Sub_Scal);
	FEUR_Test_Add_Test("Mult Scalar", Test_Vec2_Mult_Scal);

	FEUR_Test_Add_Group("In-Place Arithmetic");

	FEUR_Test_Add_Test("Add In", Test_Vec2_Add_In);
	FEUR_Test_Add_Test("Sub In", Test_Vec2_Sub_In);
	FEUR_Test_Add_Test("Add Scalar In", Test_Vec2_Add_Scal_In);
	FEUR_Test_Add_Test("Sub Scalar In", Test_Vec2_Sub_Scal_In);
	FEUR_Test_Add_Test("Mult Scalar In", Test_Vec2_Mult_Scal_In);

	FEUR_Test_Add_Group("Products & Metrics");

	FEUR_Test_Add_Test("Dot", Test_Vec2_Dot);
	FEUR_Test_Add_Test("Len", Test_Vec2_Len);
	FEUR_Test_Add_Test("Len2", Test_Vec2_Len2);
	FEUR_Test_Add_Test("Dist", Test_Vec2_Dist);
	FEUR_Test_Add_Test("Dist2", Test_Vec2_Dist2);

	FEUR_Test_Add_Group("Normalization");

	FEUR_Test_Add_Test("Norm", Test_Vec2_Norm);
	FEUR_Test_Add_Test("Norm In", Test_Vec2_Norm_In);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}

