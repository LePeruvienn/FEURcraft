#include "FEUR_Test/FEUR_Test.h"

#include "asset_loader.h"

#include "image.h"
#include "image_array.h"

#include <stdlib.h>


FEUR_Test_Result Test_ImageArray()
{
	const char* asset_path = "assets/textures/pumpkin_block.fasset";

	const char* img_array_out = "tests/out/asset_image_array_out.png";
	const char* image_array_ref = "tests/assets/asset_image_array_ref.png";

	ImageArray* img_array = asset_load_image_array(asset_path);

	FEUR_TEST_ASSERT_NOT_NULL(img_array);

	FEUR_TEST_ASSERT(image_array_write(img_array, img_array_out));

	Image* out = image_create_and_load(img_array_out);
	Image* ref = image_create_and_load(image_array_ref);

	FEUR_TEST_ASSERT(image_are_equal(out, ref));

	image_free(out);
	image_free(ref);

	image_array_free(img_array);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("Load ImageArray", Test_ImageArray);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
