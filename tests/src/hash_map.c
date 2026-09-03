#include "FEUR_Test/FEUR_Test.h"

#include "hash_map.h"

#include <stdlib.h>
#include <stdbool.h>

#define PRIME_NUMBER 193

static size_t hash_int(const void* key_ptr)
{
	int key = *((int*) key_ptr);
	return key * (key + 3) % PRIME_NUMBER; 
}

static bool compare_int(const void* a, const void* b)
{
	return (*(int*) a == *(int*) b);
}

FEUR_Test_Result Test_HashMap_SetGet()
{
	HashMap* map = hash_map_create(sizeof(int), sizeof(float), hash_int, compare_int);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create HashMap");

	int key = 5;
	float value = 2.5f;

	hash_map_set(map, &key, &value);

	float* value_ptr = hash_map_get(map, &key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	float new_value = 28;

	hash_map_set(map, &key, &new_value);

	float* new_value_ptr = hash_map_get(map, &key);

	FEUR_TEST_ASSERT_NOT_NULL(new_value_ptr);
	FEUR_TEST_ASSERT_EQUAL(new_value, *new_value_ptr);

	hash_map_free(map);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_HashMap_Del()
{
	HashMap* map = hash_map_create(sizeof(int), sizeof(float), hash_int, compare_int);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create HashMap");

	int key = 5;
	float value = 3.14f;

	hash_map_set(map, &key, &value);

	float* value_ptr = hash_map_get(map, &key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	hash_map_del(map, &key);

	float* del_value_ptr = hash_map_get(map, &key);
	FEUR_TEST_ASSERT_EQUAL(del_value_ptr, NULL);

	float new_value = 28;
	hash_map_set(map, &key, &new_value);

	float* new_value_ptr = hash_map_get(map, &key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL_MSG(new_value_ptr, value_ptr,
		"This is to test if we are reusing the space that has been deleted ?"
		" Can be not true anymore depending of youre modifications");

	hash_map_free(map);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_HashMap_Exists()
{
	HashMap* map = hash_map_create(sizeof(int), sizeof(float), hash_int, compare_int);

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create HashMap");

	int key = 5;
	float value = 3.14f;

	hash_map_set(map, &key, &value);

	bool value_exists = hash_map_exists(map, &key);

	FEUR_TEST_ASSERT(value_exists);

	hash_map_del(map, &key);

	bool del_value_exists = hash_map_exists(map, &key);
	FEUR_TEST_ASSERT_EQUAL(del_value_exists, false);

	float new_value = 28;
	hash_map_set(map, &key, &new_value);

	bool new_value_exists = hash_map_exists(map, &key);

	FEUR_TEST_ASSERT(new_value_exists);

	hash_map_free(map);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("HashMap Set and Get", Test_HashMap_SetGet);
	FEUR_Test_Add_Test("HashMap Delete", Test_HashMap_Del);
	FEUR_Test_Add_Test("HashMap Exists", Test_HashMap_Exists);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
