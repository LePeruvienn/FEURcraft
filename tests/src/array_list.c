#include "FEUR_Test/FEUR_Test.h"
#include "array_list.h"

FEUR_Test_Result Test_ArrayList_Create()
{
	ArrayList* list = array_list_create(sizeof(int), 5);

	FEUR_TEST_ASSERT_NOT_NULL(list);
	FEUR_TEST_ASSERT_NOT_NULL(list->data);
	FEUR_TEST_ASSERT(list->item_size == sizeof(int));
	FEUR_TEST_ASSERT(list->capacity == 5);
	FEUR_TEST_ASSERT(list->count == 0);

	array_list_free(list);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Push_Get()
{
	ArrayList* list = array_list_create(sizeof(int), 3);
	
	int val1 = 42;
	int val2 = 84;
	int val3 = 99;

	array_list_push(list, &val1);
	array_list_push(list, &val2);
	array_list_push(list, &val3);

	FEUR_TEST_ASSERT(list->count == 3);

	int* get1 = (int*) array_list_get(list, 0);
	int* get2 = (int*) array_list_get(list, 1);
	int* get3 = (int*) array_list_get(list, 2);

	FEUR_TEST_ASSERT_NOT_NULL(get1);
	FEUR_TEST_ASSERT_NOT_NULL(get2);
	FEUR_TEST_ASSERT_NOT_NULL(get3);

	FEUR_TEST_ASSERT(*get1 == 42);
	FEUR_TEST_ASSERT(*get2 == 84);
	FEUR_TEST_ASSERT(*get3 == 99);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Clear()
{
	ArrayList* list = array_list_create(sizeof(int), 5);
	
	int val = 10;
	array_list_push(list, &val);
	array_list_push(list, &val);

	FEUR_TEST_ASSERT(list->count == 2);

	array_list_clear(list);

	// Le count doit revenir à 0, mais la capacité doit rester intacte
	FEUR_TEST_ASSERT(list->count == 0);
	FEUR_TEST_ASSERT(list->capacity == 5);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_AutoResize()
{
	ArrayList* list = array_list_create(sizeof(int), 8);
	
	int val = 7;
	array_list_push(list, &val);

	FEUR_TEST_ASSERT(list->capacity == 8);
	FEUR_TEST_ASSERT(list->count == 1);

	for (int i = 1; i <= 8; i++) 
	{
		array_list_push(list, &i);
	}

	FEUR_TEST_ASSERT(list->count == 9);
	FEUR_TEST_ASSERT(list->capacity >= 9);

	int* first_elem = (int*) array_list_get(list, 0);

	FEUR_TEST_ASSERT(*first_elem == 7);

	array_list_free(list);

	return FEUR_Test_Success;
}


int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Lancement des tests de l'ArrayList...");

	FEUR_Test_Add_Group("ArrayList - Opérations de base");
	FEUR_Test_Add_Test("Création d'une liste", Test_ArrayList_Create);
	FEUR_Test_Add_Test("Push et Get", Test_ArrayList_Push_Get);
	FEUR_Test_Add_Test("Clear de la liste", Test_ArrayList_Clear);

	FEUR_Test_Add_Group("ArrayList - Gestion Mémoire");
	FEUR_Test_Add_Test("Redimensionnement Auto", Test_ArrayList_AutoResize);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
