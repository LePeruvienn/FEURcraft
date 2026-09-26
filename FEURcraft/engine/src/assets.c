#include "assets.h"

#include "array_list.h"
#include "string_hash_map.h"

#include "image.h"
#include "image_array.h"
#include "texture.h"
#include "texture_array.h"
#include "shader_program.h"
#include "geometry.h"
#include "mesh.h"

#include "error_checker.h"
#include "call_once.h"

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define ASSETS_PATH_MAX_SIZE 128

// vvvv QUI A ECRKI ÇA !!!!!!!!!!!!! 😠
// Arthur est le boss des boss ! :D
static bool is_init = false;

static Assets assets = 
{
	.images = NULL,
	.image_arrays = NULL,
	.textures = NULL,
	.texture_arrays = NULL,
	.shaders = NULL,
	.shader_programs = NULL,
	.geometries = NULL,
	.meshes = NULL
};

void assets_init(const char* program_path)
{
	CHECK_IS_NULL_RET(program_path,
		"Cannot init Assets with a NULL program path", )

	CHECK_COND_RET(is_init == false, 
		"Assets are already intialized", );

	// size_t len = strlen(program_path);

	// TODO!!

	assets.images = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(Image*));
	assets.image_arrays = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(ImageArray*));
	assets.textures = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(Texture*));
	assets.texture_arrays = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(TextureArray*));

	is_init = true;
}

/*static*/ bool assets_get_raw_file_path(const char* file_path, char* buffer, size_t size)
{
	CHECK_IS_NULL_RET(file_path, "Cannot get raw file path of a NULL char*", false);
	CHECK_IS_NULL_RET(buffer, "Cannot give raw file path to a NULL output buffer", false);

	size_t len = strlen(file_path);

	size_t min_len = (size < len) ? size : len;

	if(file_path[0] == '/')
	{
		memcpy(buffer, file_path, min_len);
		return true;
	}

	// TODO !!!!

	return true;
}

Image* assets_get_image(const char* image_path)
{
	Image* image = NULL;
	bool exists = string_hash_map_get(assets.images, image_path, &image);

	if (exists == false || image == NULL)
	{
		image = image_create(image_path);

		CHECK_IS_NULL_RET(image, "Failed to create image when getting asset", NULL);

		string_hash_map_set(assets.images, image_path, &image);
	}

	CHECK_IS_NULL_RET(image, "Failed to get image from assets", NULL);

	return image;
}


