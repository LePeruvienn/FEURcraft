#include "FEUR_Test/FEUR_Test.h"

#include "hash_map.h"

#include <stdlib.h>

FEUR_Test_Result Test_HashMap()
{
    HashMap* map = hash_map_create(sizeof(int));

    FEUR_TEST_ASSERT_NOT_NULL_MSG(map, "Failed to create HashMap");

    int value = 2;
    int key = 5;
    
    hash_map_set(map, key, &value);

    int* value_ptr = hash_map_get(map, key);
    
    FEUR_TEST_ASSERT_NOT_NULL(value_ptr);
    FEUR_TEST_ASSERT_EQUAL(value, *value_ptr);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("HashMap Test", Test_HashMap);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
