#ifndef ASSET_H
#define ASSET_H

#include "array_list.h"
#include "string_hash_map.h"

#include "image.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define ASSETS_MAX_ORIGIN_LEN 256

typedef enum AssetType AssetType;

enum AssetType
{
	ASSET_TYPE_INVALID = 0,

	ASSET_TYPE_IMAGE,
	ASSET_TYPE_TEXTURE,
	ASSET_TYPE_TEXTURE_ARRAY,
	ASSET_TYPE_SHADER,
	ASSET_TYPE_SHADER_PROGRAM,
	ASSET_TYPE_GEOMETRY,
	ASSET_TYPE_MESH,

	ASSET_TYPE_COUNT
};

typedef struct AssetHandle AssetHandle;

struct AssetHandle
{
	AssetType type;

	size_t id;
	const char* file_path;

	bool is_loaded;
};

typedef struct Assets Assets;

struct Assets
{
	const char origin_path[ASSETS_MAX_ORIGIN_LEN];

	StringHashMap* images;
	StringHashMap* image_arrays;
	StringHashMap* textures;
	StringHashMap* texture_arrays;
	StringHashMap* shaders;
	StringHashMap* shader_programs;
	StringHashMap* geometries;
	StringHashMap* meshes;
};

void assets_init(const char* program_path);

Image* assets_get_image(const char* image_path);

void assets_deinit();

#endif // ASSET_H
