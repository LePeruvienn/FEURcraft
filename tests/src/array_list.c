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

FEUR_Test_Result Test_ArrayList_Push_Buffer()
{
	ArrayList* list = array_list_create(sizeof(int), 2);
	
	int buffer[5] = {10, 20, 30, 40, 50};
	
	array_list_push_buffer(list, buffer, 5);
	
	FEUR_TEST_ASSERT(list->count == 5);
	
	FEUR_TEST_ASSERT(list->capacity >= 5);
	
	int* get_first = (int*)array_list_get(list, 0);
	int* get_last  = (int*)array_list_get(list, 4);
	
	FEUR_TEST_ASSERT_NOT_NULL(get_first);
	FEUR_TEST_ASSERT_NOT_NULL(get_last);
	
	FEUR_TEST_ASSERT(*get_first == 10);
	FEUR_TEST_ASSERT(*get_last == 50);

	int buffer_2[2] = {60, 70};
	array_list_push_buffer(list, buffer_2, 2);

	FEUR_TEST_ASSERT(list->count == 7);
	int* get_new_last = (int*)array_list_get(list, 6);
	FEUR_TEST_ASSERT(*get_new_last == 70);
	
	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Push_Array()
{
	ArrayList* list_a = array_list_create(sizeof(int), 2);
	ArrayList* list_b = array_list_create(sizeof(int), 3);

	int a_vals[2] = {1, 2};
	array_list_push_buffer(list_a, a_vals, 2);

	int b_vals[3] = {3, 4, 5};
	array_list_push_buffer(list_b, b_vals, 3);

	array_list_push_array(list_a, list_b);

	FEUR_TEST_ASSERT(list_a->count == 5);
	FEUR_TEST_ASSERT(list_a->capacity >= 5);

	int* val_0 = (int*) array_list_get(list_a, 0);
	int* val_2 = (int*) array_list_get(list_a, 2);
	int* val_4 = (int*) array_list_get(list_a, 4);

	FEUR_TEST_ASSERT_NOT_NULL(val_0);
	FEUR_TEST_ASSERT_NOT_NULL(val_2);
	FEUR_TEST_ASSERT_NOT_NULL(val_4);

	FEUR_TEST_ASSERT(*val_0 == 1);
	FEUR_TEST_ASSERT(*val_2 == 3);
	FEUR_TEST_ASSERT(*val_4 == 5);

	FEUR_TEST_ASSERT(list_b->count == 3);
	int* b_val_0 = (int*) array_list_get(list_b, 0);
	FEUR_TEST_ASSERT(*b_val_0 == 3);

	array_list_free(list_a);
	array_list_free(list_b);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Static()
{
	// Buffer alloué sur la Stack
	int stack_buffer[5];

	ArrayList list = ARRAY_LIST_STATIC(stack_buffer, sizeof(int), 0, 5);

	FEUR_TEST_ASSERT(list.is_static == true);
	FEUR_TEST_ASSERT(list.count == 0);
	FEUR_TEST_ASSERT(list.capacity == 5);

	int v1 = 10, v2 = 20, v3 = 30;
	array_list_push(&list, &v1);
	array_list_push(&list, &v2);
	array_list_push(&list, &v3);

	FEUR_TEST_ASSERT(list.count == 3);

	int* val_0 = (int*)array_list_get(&list, 0);
	int* val_2 = (int*)array_list_get(&list, 2);

	FEUR_TEST_ASSERT_NOT_NULL(val_0);
	FEUR_TEST_ASSERT_NOT_NULL(val_2);
	FEUR_TEST_ASSERT(*val_0 == 10);
	FEUR_TEST_ASSERT(*val_2 == 30);

	FEUR_TEST_ASSERT(stack_buffer[0] == 10);
	FEUR_TEST_ASSERT(stack_buffer[2] == 30);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Lancement des tests de l'ArrayList...");

	FEUR_Test_Add_Group("ArrayList - Opérations de base");
	FEUR_Test_Add_Test("Création d'une liste", Test_ArrayList_Create);
	FEUR_Test_Add_Test("Push et Get", Test_ArrayList_Push_Get);
	FEUR_Test_Add_Test("Push de buffer", Test_ArrayList_Push_Buffer);
	FEUR_Test_Add_Test("Clear de la liste", Test_ArrayList_Clear);
	FEUR_Test_Add_Test("Push Array", Test_ArrayList_Push_Array);
	FEUR_Test_Add_Test("ArrayList static",Test_ArrayList_Static);

	FEUR_Test_Add_Group("ArrayList - Gestion Mémoire");
	FEUR_Test_Add_Test("Redimensionnement Auto", Test_ArrayList_AutoResize);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
