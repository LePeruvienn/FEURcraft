#ifndef MATERIAL_H
#define MATERIAL_H

#include "feur_types.h"

#include "vec2.h"
#include "vec3.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#include "string_hash_map.h"

#include <stdbool.h>

#define MAT_NAME_SIZE 32

typedef enum MaterialPropertyType MaterialPropertyType;

enum MaterialPropertyType
{
	MAT_PROPERTY_TYPE_EMPTY = 0,

	MAT_PROPERTY_TYPE_INT,
	MAT_PROPERTY_TYPE_UINT,
	MAT_PROPERTY_TYPE_FLOAT,
	MAT_PROPERTY_TYPE_VEC2,
	MAT_PROPERTY_TYPE_VEC3,
	MAT_PROPERTY_TYPE_VEC4
};

typedef struct MaterialProperty MaterialProperty;

struct MaterialProperty
{
	char name[MAT_NAME_SIZE];
	MaterialPropertyType type;

	union
	{
		int int_value;
		uint uint_value;
		float float_value;

		Vec2 vec2_value;
		Vec3 vec3_value;
		Vec4 vec4_value;
	};
};

typedef struct Material Material;

struct Material
{
	char name[MAT_NAME_SIZE];
	StringHashMap* properties;
};

Material* material_create(const char* name);

void material_free(Material* material);

bool material_add_property(Material* material, const char* name, MaterialPropertyType type);

bool material_exists_property(Material* material, const char* name);

bool material_remove_property(Material* material, const char* name);

bool material_set_property(Material* material, const char* name, MaterialPropertyType type, void* data);

MaterialProperty material_get_property(Material* material, const char* name);

MaterialProperty* material_get_property_modify(Material* material, const char* name);

int material_property_get_int();

bool material_set_property_int(Material* material, const char* name, int value);
bool material_set_property_uint(Material* material, const char* name, uint value);
bool material_set_property_float(Material* material, const char* name, float value);
bool material_set_property_vec2(Material* material, const char* name, Vec2 value);
bool material_set_property_vec3(Material* material, const char* name, Vec3 value);
bool material_set_property_vec4(Material* material, const char* name, Vec4 value);

#endif // MATERIAL_H
