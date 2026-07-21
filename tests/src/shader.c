#include "FEUR_Test/FEUR_Test.h"

#include "glad/glad.h"

#include "shader.h"

#define TEST_VERTEX_SHADER "tests/assets/simple.vert"
#define TEST_FRAGMENT_SHADER "tests/assets/simple.frag"
#define TEST_ERROR_SHADER "tests/assets/error.vert"

FEUR_Test_Result Test_Shader_Create()
{
	Shader* shader = shader_create(
		TEST_VERTEX_SHADER,
		SHADER_TYPE_VERT
	);

	FEUR_TEST_ASSERT_NOT_NULL(shader);

	FEUR_TEST_ASSERT(shader->id != 0);
	FEUR_TEST_ASSERT(shader->type == SHADER_TYPE_VERT);
	FEUR_TEST_ASSERT(
		shader->status == SHADER_STATUS_NOT_COMPILED
	);

	shader_free(shader);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader_Create_Fragment()
{
	Shader* shader = shader_create(
		TEST_FRAGMENT_SHADER,
		SHADER_TYPE_FRAG
	);

	FEUR_TEST_ASSERT_NOT_NULL(shader);

	FEUR_TEST_ASSERT(shader->type == SHADER_TYPE_FRAG);

	shader_free(shader);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader_Invalid_Type()
{
	Shader* shader = shader_create(
		"test.vert",
		SHADER_TYPE_COUNT
	);

	FEUR_TEST_ASSERT_NULL(shader);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader_Compile()
{
	Shader* shader = shader_create(
		TEST_VERTEX_SHADER,
		SHADER_TYPE_VERT
	);

	FEUR_TEST_ASSERT_NOT_NULL(shader);

	shader_compile(shader);

	FEUR_TEST_ASSERT(
		shader->status == SHADER_STATUS_COMPILED
	);

	shader_free(shader);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader_Compile_Error()
{
	Shader* shader = shader_create(
		TEST_ERROR_SHADER,
		SHADER_TYPE_VERT
	);

	FEUR_TEST_ASSERT_NOT_NULL(shader);

	shader_compile(shader);

	FEUR_TEST_ASSERT(
		shader->status == SHADER_STATUS_COMPILE_FAILED
	);


	shader_free(shader);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader_Recompile()
{
	Shader* shader = shader_create(
		TEST_VERTEX_SHADER,
		SHADER_TYPE_VERT
	);

	shader_compile(shader);

	FEUR_TEST_ASSERT(
		shader->status == SHADER_STATUS_COMPILED
	);

	shader_compile(shader);

	FEUR_TEST_ASSERT(
		shader->status == SHADER_STATUS_COMPILED
	);

	shader_free(shader);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader_Free_Null()
{
	shader_free(NULL);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	// TO FIX
	if (!gladLoadGL())
	{
		LOG_ERROR("Failed to initialize glad.");
		exit(EXIT_FAILURE);
	}

	FEUR_Test_Add_Group("Shader");

	FEUR_Test_Add_Test(
		"Create Vertex Shader",
		Test_Shader_Create
	);

	FEUR_Test_Add_Test(
		"Create Fragment Shader",
		Test_Shader_Create_Fragment
	);

	FEUR_Test_Add_Test(
		"Invalid Shader Type",
		Test_Shader_Invalid_Type
	);

	FEUR_Test_Add_Test(
		"Compile Shader",
		Test_Shader_Compile
	);

	FEUR_Test_Add_Test(
		"Compile Failed Shader",
		Test_Shader_Compile_Error
	);

	FEUR_Test_Add_Test(
		"Recompile Shader",
		Test_Shader_Recompile
	);

	FEUR_Test_Add_Test(
		"Free NULL Shader",
		Test_Shader_Free_Null
	);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}

