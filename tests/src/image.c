#include "FEUR_Test/FEUR_Test.h"

#include "image.h"

FEUR_Test_Result Test_load_PNG()
{
	Image* img = image_create("tests/assets/gold_block.png");

	FEUR_TEST_ASSERT_MSG(img != NULL,
		"Failed to create Image.");

	image_load(img);

	FEUR_TEST_ASSERT_MSG(image_is_loaded(img),
		"Failed to load Image.");

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_write_PNG()
{
	const char* in_path = "tests/assets/gold_block.png";
	const char* out_path = "tests/out/test_write_image.png";

	Image* img_in = image_create(in_path);

	FEUR_TEST_ASSERT_MSG(img_in != NULL,
		"Failed to create in Image.");

	image_load(img_in);

	FEUR_TEST_ASSERT_MSG(image_is_loaded(img_in),
		"Failed to load in Image.");

	image_write(img_in, out_path);

	Image* img_out = image_create(out_path);

	FEUR_TEST_ASSERT_MSG(img_out != NULL,
		"Failed to create out Image.");

	image_load(img_out);

	FEUR_TEST_ASSERT_MSG(image_is_loaded(img_out),
		"Failed to load out Image.");

	FEUR_TEST_ASSERT_MSG(image_are_equal(img_in, img_out),
		"Images are not equal !");

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("Load Image", Test_load_PNG);
	FEUR_Test_Add_Test("Write Image", Test_write_PNG);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
