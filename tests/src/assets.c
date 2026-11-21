#include "FEUR_Test/FEUR_Test.h"

#include "assets.h"
#include "shader.h"

#include <stdlib.h>

FEUR_Test_Result Test_Image()
{
	const char* image_path = "tests/assets/gold_block.png";

	FEUR_TEST_LOG_INFO("Loading image \"%s\"", image_path);

	Image* image = assets_get_image(image_path);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(image_path, "Failed to get image");

	Image* cached = assets_get_image(image_path);

	FEUR_TEST_ASSERT_MSG(image == cached, "Image caching does not work!");

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Shader()
{
	const char* vert_shader_path = "tests/assets/simple.vert";
	const char* frag_shader_path ="tests/assets/simple.frag";

	FEUR_TEST_LOG_INFO("Loading vertex shader \"%s\"", vert_shader_path);
	FEUR_TEST_LOG_INFO("Loading fragment shader \"%s\"", frag_shader_path);

	Shader* vert_shader = assets_get_shader(vert_shader_path);
	Shader* frag_shader = assets_get_shader(frag_shader_path);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(vert_shader, "Failed to get vert shader");
	FEUR_TEST_ASSERT_NOT_NULL_MSG(frag_shader, "Failed to get frag shader");

	FEUR_TEST_ASSERT_MSG(vert_shader->type == SHADER_TYPE_VERT,
		"Vertex shader type mismatch");

	FEUR_TEST_ASSERT_MSG(frag_shader->type == SHADER_TYPE_FRAG,
		"Fragment shader type mismatch");

	Shader* vert_cached = assets_get_shader(vert_shader_path);
	Shader* frag_cached = assets_get_shader(frag_shader_path);

	FEUR_TEST_ASSERT_MSG(vert_cached == vert_shader,
		"Vertex shader caching dont work!");

	FEUR_TEST_ASSERT_MSG(frag_cached == frag_shader,
		"Fragment shader caching dont work!");

	shader_free(vert_shader);
	shader_free(frag_shader);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init_With_GL();

	FEUR_Test_Add_Test("Assets Image", Test_Image);
	FEUR_Test_Add_Test("Assets Shader", Test_Shader);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
