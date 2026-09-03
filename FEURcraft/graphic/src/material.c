#include "material.h"

#include "ptr_helper.h"
#include "error_checker.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static MaterialProperty MAT_PROPERTY_EMPTY = { 0 };

Material* material_create(const char* name)
{
	CHECK_IS_NULL_RET(name, "Cannot create a material with a NULL name", NULL);

	size_t name_len = strlen(name);

	CHECK_COND_RET(name_len < MAT_NAME_SIZE,
		"Cannot create a material with a name too big.", NULL);

	Material* material = malloc(sizeof(struct Material));

	CHECK_IS_NULL_RET(material, "Failed to malloc material", NULL);

	strcpy(material->name, name);
	material->name[name_len] = '\0';

	material->properties = string_hash_map_create(MAT_NAME_SIZE, sizeof(struct MaterialProperty));

	if (material->properties == NULL)
	{
		LOG_ERROR("Failed to create Material properties StrinHashMap");
		free(material);
		return NULL;
	}

	return material;
}

void material_free(Material* material)
{
	CHECK_IS_NULL_RET(material, "Cannot free a NULL Material", )
	FREE_PTR_NOT_NULL(material->properties, string_hash_map_free);
	free(material);
}

bool material_add_property(Material* material, const char* name, MaterialPropertyType type)
{
	CHECK_IS_NULL_RET(material, "Cannot add property of a NULL Material", false);
	CHECK_IS_NULL_RET(name, "Cannot add property to Material with NULL name", false);

	CHECK_IS_NULL_RET(material->properties,
		"Material properties is NULL, corruption detected", false);

	CHECK_COND_RET(material_exists_property(material, name) == false,
		"Cannotc checkadd new Material Property it already exists", false);

	MaterialProperty property = MAT_PROPERTY_EMPTY;
	property.type = type;

	string_hash_map_set(material->properties, name, &property);

	return true;
};

bool material_exists_property(Material* material, const char* name)
{
	CHECK_IS_NULL_RET(material, "Cannot check exists property of a NULL Material", false);
	CHECK_IS_NULL_RET(name, "Cannot check exists property to Material with NULL name", false);

	CHECK_IS_NULL_RET(material->properties,
		"Material properties is NULL, corruption detected", false);

	return string_hash_map_exists(material->properties, name);
}

bool material_remove_property(Material* material, const char* name)
{
	CHECK_IS_NULL_RET(material, "Cannot remove a property of a NULL Material", false);
	CHECK_IS_NULL_RET(name, "Cannot remove a property to Material with NULL name", false);

	CHECK_IS_NULL_RET(material->properties,
		"Material properties is NULL, corruption detected", false);

	CHECK_COND_RET(material_exists_property(material, name) == true,
		"Cannot remove a Material Property it already exists", false);

	string_hash_map_del(material->properties, name);

	return true;
}

static size_t material_property_type_size(MaterialPropertyType type)
{
	switch(type)
	{
		case MAT_PROPERTY_TYPE_EMPTY:
			LOG_ERROR("Tried to get MaterialProperty size of type empty.");
			return 0;

		case MAT_PROPERTY_TYPE_INT:
			return sizeof(int);

		case MAT_PROPERTY_TYPE_UINT:
			return sizeof(unsigned int);

		case MAT_PROPERTY_TYPE_FLOAT:
			return sizeof(float);

		case MAT_PROPERTY_TYPE_VEC2:
			return sizeof(Vec2);

		case MAT_PROPERTY_TYPE_VEC3:
			return sizeof(Vec3);

		case MAT_PROPERTY_TYPE_VEC4:
			return sizeof(Vec4);
	}

	LOG_ERROR("Unkown MaterialPropertyType, returned 0");
	return 0;
}

bool material_set_property(Material* material, const char* name, MaterialPropertyType type, void* data)
{
	CHECK_IS_NULL_RET(material, "Cannot set a property of a NULL Material", false);
	CHECK_IS_NULL_RET(name, "Cannot set a property to Material with NULL name", false);

	CHECK_IS_NULL_RET(material->properties,
		"Material properties is NULL, corruption detected", false);

	CHECK_COND_RET(material_exists_property(material, name) == true,
		"Cannot set a Material Property that dont exists", false);

	MaterialProperty* property = material_get_property_modify(material, name);

	CHECK_COND_RET(property->type == type,
		"Cannot set Material Property types dont match.", false);

	size_t type_size = material_property_type_size(type);

	CHECK_COND_RET(type_size > 0, "Failed to get MaterialPropertyType size", false);

	memcpy(&property->int_value, data, type_size);

	return true;
}

MaterialProperty material_get_property(Material* material, const char* name)
{
	const MaterialProperty* property_ptr = material_get_property_modify(material, name);

	CHECK_IS_NULL_RET(property_ptr, "Failed to get MaterialProperty", MAT_PROPERTY_EMPTY);

	return *property_ptr;
}

MaterialProperty* material_get_property_modify(Material* material, const char* name)
{
	CHECK_IS_NULL_RET(material, "Cannot get a property of a NULL Material", NULL);
	CHECK_IS_NULL_RET(name, "Cannot get a property to Material with NULL name", NULL);

	CHECK_IS_NULL_RET(material->properties,
		"Material properties is NULL, corruption detected", NULL);

	CHECK_COND_RET(material_exists_property(material, name) == true,
		"Cannot get a Material Property that dont exists", NULL);

	MaterialProperty* property = string_hash_map_get(material->properties, name);

	CHECK_IS_NULL(property, "Failed to get Material Property");

	return property;
}

bool material_set_property_int(Material* material, const char* name, int value)
{
	return material_set_property(material, name, MAT_PROPERTY_TYPE_INT, &value);
}

bool material_set_property_uint(Material* material, const char* name, uint value)
{
	return material_set_property(material, name, MAT_PROPERTY_TYPE_UINT, &value);
}

bool material_set_property_float(Material* material, const char* name, float value)
{
	return material_set_property(material, name, MAT_PROPERTY_TYPE_FLOAT, &value);
}

bool material_set_property_vec2(Material* material, const char* name, Vec2 value)
{
	return material_set_property(material, name, MAT_PROPERTY_TYPE_VEC2, &value);
}
bool material_set_property_vec3(Material* material, const char* name, Vec3 value)
{
	return material_set_property(material, name, MAT_PROPERTY_TYPE_VEC3, &value);
}

bool material_set_property_vec4(Material* material, const char* name, Vec4 value)
{
	return material_set_property(material, name, MAT_PROPERTY_TYPE_VEC4, &value);
}
