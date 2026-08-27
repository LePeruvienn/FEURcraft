#include "FEUR_Test/FEUR_Test.h"

#include "hash_map.h"

#include <stdlib.h>

FEUR_Test_Result Test_HashMap_SetGet()
{
	HashMap* map = hash_map_create(sizeof(int));

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create HashMap");

	int value = 2;
	int key = 5;

	hash_map_set(map, key, &value);

	int* value_ptr = hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	int new_value = 28;

	hash_map_set(map, key, &new_value);

	int* new_value_ptr = hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(new_value_ptr);
	FEUR_TEST_ASSERT_EQUAL(new_value, *new_value_ptr);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_HashMap_Del()
{
	HashMap* map = hash_map_create(sizeof(int));

	FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create HashMap");

	int value = 2;
	int key = 5;

	hash_map_set(map, key, &value);

	int* value_ptr = hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	hash_map_del(map, key);

	int* del_value_ptr = hash_map_get(map, key);
	FEUR_TEST_ASSERT_EQUAL(del_value_ptr, NULL);

	int new_value = 28;
	hash_map_set(map, key, &new_value);

	int* new_value_ptr = hash_map_get(map, key);

	FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
	FEUR_TEST_ASSERT_EQUAL_MSG(new_value_ptr, value_ptr,
		"This is to test if we are reusing the space that has been deleted ?"
		" Can be not true anymore depending of youre modifications");

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("HashMap Set and Get", Test_HashMap_SetGet);
	FEUR_Test_Add_Test("HashMap Delete", Test_HashMap_Del);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
