#include "FEUR_Test/FEUR_Test.h"

#include "atlas.h"

#define TEXTURE_WIDTH 16
#define TEXTURE_HEIGHT 16

#define TEXTURE_PER_ROW 4
#define TEXTURE_PER_COL 4

unsigned int atlas_width = TEXTURE_WIDTH * TEXTURE_PER_ROW;
unsigned int atlas_height = TEXTURE_HEIGHT * TEXTURE_PER_COL;
unsigned int atlas_channels = 4;

const char* img_path1 = "tests/assets/gold_ore.png";
const char* img_path2 = "tests/assets/gold_block.png";
const char* img_path3 = "tests/assets/log_oak.png";

const char* atlas_out = "tests/out/atlas_out.png";
const char* atlas_ref = "tests/assets/atlas_out_ref.png";

Atlas* atlas = NULL;

FEUR_Test_Result Test_Atlas_create()
{
	atlas = atlas_create(atlas_width,
	                     atlas_height,
	                     atlas_channels);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(atlas, 
		"Failed to create Atlas");

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Atlas_add_image()
{
	FEUR_TEST_ASSERT_NOT_NULL_MSG(atlas,
		"Cannot add images to a NULL atlas");

	#define IMAGES_SIZE 3

	Image* images[IMAGES_SIZE] =
	{
		image_create_and_load(img_path1),
		image_create_and_load(img_path2),
		image_create_and_load(img_path3)
	};

	for (unsigned int i = 0; i < IMAGES_SIZE ; ++i)
	{
		FEUR_TEST_ASSERT_NOT_NULL_MSG(images[i],
			"Some image(s) failed to load.");
	}

	unsigned int total_texture_amount = TEXTURE_PER_COL * TEXTURE_PER_ROW;

	for (unsigned int i = 0; i < total_texture_amount; ++i)
	{
		TextureCoords tmp;

		unsigned int index = i % IMAGES_SIZE;

		FEUR_TEST_ASSERT_MSG(atlas_add_image(atlas, images[index], &tmp), 
			"Failed to add Image to Altas.");
	}

	for (unsigned int i = 0; i < IMAGES_SIZE ; ++i)
	{
		image_free(images[i]);
	}

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Atlas_write_and_compare()
{
	FEUR_TEST_ASSERT_NOT_NULL_MSG(atlas,
		"Cannot write and compare a NULL atlas");

	atlas_write_image(atlas, atlas_out);

	Image* img_atlas = image_create_and_load(atlas_out);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(img_atlas,
		"Failed to write Atlas.");

	Image* img_ref = image_create_and_load(atlas_ref);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(img_ref,
		"Failed to load Atlas Image reference");

	FEUR_TEST_ASSERT_MSG(image_are_equal(img_atlas, img_ref) == true, 
		"Atlas ref and outpiut are not equal !");

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("Atlas create", Test_Atlas_create);
	FEUR_Test_Add_Test("Atlas add images", Test_Atlas_add_image);
	FEUR_Test_Add_Test("Atlas write and compare", Test_Atlas_write_and_compare);

	FEUR_Test_Run();

	FEUR_Test_End();

	atlas_free(atlas);

	return 0;
}
