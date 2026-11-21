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

static void* get_cached_asset(StringHashMap* map, const char* key)
{
	void* asset = NULL;
	bool exist = string_hash_map_get(map, key, &asset);

	if (exist && asset == NULL)
	{
		LOG_WARNING("Asset Map returned true, but ptr is NULL");
	}

	if (exist == false || asset == NULL)
	{
		return NULL;
	}

	return asset;
}

void assets_init()
{
	if (is_init)
	{
		return;
	}

	assets.images = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(Image*));
	assets.image_arrays = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(ImageArray*));

	assets.textures = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(Texture*));
	assets.texture_arrays = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(TextureArray*));

	assets.shaders = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(Shader*));
	assets.shader_programs = string_hash_map_create(ASSETS_PATH_MAX_SIZE, sizeof(ShaderProgram*));

	is_init = true;
}

#define ASSETS_INIT_IF_NEEDED() \
	if(is_init == false) { assets_init(); }

Image* assets_get_image(const char* image_path)
{
	ASSETS_INIT_IF_NEEDED();

	Image* image = NULL;
	image = get_cached_asset(assets.images, image_path);

	if (image != NULL)
	{
		return image;
	}

	image = image_create(image_path);

	CHECK_IS_NULL_RET(image, "Failed to create image when getting asset", NULL);

	string_hash_map_set(assets.images, image_path, &image);

	return image;
}

static bool get_shader_type_from_path(const char* shader_path, ShaderType* out)
{
	CHECK_IS_NULL_RET(shader_path, "Cannot get ShaderType from NULL str.", false)
	CHECK_IS_NULL_RET(out, "Cannot out ShaderType to NULL.", false)

	const char dot = '.';

	char* last_dot = strrchr(shader_path, dot);

	CHECK_IS_NULL_RET(last_dot, "Shader file name incorrect, could not find '.' char.", false);

	last_dot += 1;

	const char* vert_ext = "vert";
	const char* frag_ext = "frag";

	bool sucess = false;

	if (strcasecmp(last_dot, vert_ext) == 0)
	{
		*out = SHADER_TYPE_VERT;
		sucess = true;
	}
	else if (strcasecmp(last_dot, frag_ext) == 0)
	{
		*out = SHADER_TYPE_FRAG;
		sucess = true;
	}

	return sucess;
}

Shader* assets_get_shader(const char* shader_path)
{
	ASSETS_INIT_IF_NEEDED();

	Shader* shader = NULL;
	shader = get_cached_asset(assets.shaders, shader_path);

	if (shader != NULL)
	{
		return shader;
	}

	ShaderType shader_type = SHADER_TYPE_COUNT;

	CHECK_COND_RET(get_shader_type_from_path(shader_path, &shader_type),
		"Failed to get shader type from file extension (must be .vert or .frag).", NULL);

	shader = shader_create(shader_path, shader_type);

	CHECK_IS_NULL_RET(shader, "Failed to create shader", NULL);

	string_hash_map_set(assets.shaders, shader_path, &shader);

	return shader;
}


