#include "FEUR_Test/FEUR_Test.h"

#include "string_hash_map.h"

#include <stdlib.h>
#include <stdbool.h>

#define STR_MAX_SIZE 32

FEUR_Test_Result Test_StringHashMap_SetGet()
{
	StringHashMap* map = string_hash_map_create(STR_MAX_SIZE, sizeof(float));

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create StringHashMap");

	const char* key = "hello";
	float value = 2.5f;

	string_hash_map_set(map, key, &value);

	float* value_ptr = string_hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	float new_value = 28;

	string_hash_map_set(map, key, &new_value);

	float* new_value_ptr = string_hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(new_value_ptr);
	FEUR_TEST_ASSERT_EQUAL(new_value, *new_value_ptr);

	string_hash_map_free(map);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_StringHashMap_Del()
{
	StringHashMap* map = string_hash_map_create(STR_MAX_SIZE, sizeof(float));

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create StringHashMap");

	const char* key = "world";
	float value = 3.14f;

	string_hash_map_set(map, key, &value);

	float* value_ptr = string_hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	string_hash_map_del(map, key);

	float* del_value_ptr = string_hash_map_get(map, key);
	FEUR_TEST_ASSERT_EQUAL(del_value_ptr, NULL);

	float new_value = 28;
	string_hash_map_set(map, key, &new_value);

	float* new_value_ptr = string_hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL_MSG(new_value_ptr, value_ptr,
		"This is to test if we are reusing the space that has been deleted ?"
		" Can be not true anymore depending of youre modifications");

	string_hash_map_free(map);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("StringHashMap Set and Get", Test_StringHashMap_SetGet);
	FEUR_Test_Add_Test("StringHashMap Delete", Test_StringHashMap_Del);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
