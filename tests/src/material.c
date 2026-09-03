#include "FEUR_Test/FEUR_Test.h"

#include "material.h"

#include "vec4.h"

FEUR_Test_Result Test_Material_Create()
{
	Material* material = material_create("TestMaterial");

	FEUR_TEST_ASSERT_NOT_NULL_MSG(material,
		"Failed to create Material");

	material_free(material);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Material_Add_Remove_Property()
{
	Material* material = material_create("TestMaterial");

	FEUR_TEST_ASSERT_NOT_NULL_MSG(material,
		"Failed to create Material");

	const char* property_name = "color";
	material_add_property(material, property_name, MAT_PROPERTY_TYPE_VEC4);

	FEUR_TEST_ASSERT(material_exists_property(material, property_name));

	material_remove_property(material, property_name);

	FEUR_TEST_ASSERT_EQUAL(material_exists_property(material, property_name), false);

	material_free(material);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Material_Set_Get_Property()
{
	Material* material = material_create("TestMaterial");

	FEUR_TEST_ASSERT_NOT_NULL_MSG(material,
		"Failed to create Material");

	const char* property_name = "color";
	material_add_property(material, property_name, MAT_PROPERTY_TYPE_VEC4);

	FEUR_TEST_ASSERT(material_exists_property(material, property_name));

	Vec4 color = VEC4(1.f, 0.f, 0.f, 1.f);

	material_set_property(material, property_name, MAT_PROPERTY_TYPE_VEC4, &color);

	MaterialProperty property = material_get_property(material, property_name);

	FEUR_TEST_ASSERT(vec4_equal(color, property.vec4_value));

	material_free(material);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("Material Create", Test_Material_Create);
	FEUR_Test_Add_Test("Material Add Remove Property", Test_Material_Add_Remove_Property);
	FEUR_Test_Add_Test("Material Set Get Property", Test_Material_Set_Get_Property);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}

