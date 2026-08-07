#include "FEUR_Test/FEUR_Test.h"

#include "array_list.h"

FEUR_Test_Result Test_ArrayList_Create_Free()
{
	ArrayList* list = array_list_create(sizeof(int), 4);

	FEUR_TEST_ASSERT_EQUAL(list->length, 0);
	FEUR_TEST_ASSERT_EQUAL(list->capacity, 4);
	FEUR_TEST_ASSERT_EQUAL(list->item_size, sizeof(int));
	FEUR_TEST_ASSERT_EQUAL(array_list_is_empty(list), true);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Push_Pop_Int()
{
	ArrayList* list = array_list_create(sizeof(int), 2);
	int a = 10;
	int b = 20;

	array_list_push(list, &a);
	array_list_push(list, &b);

	FEUR_TEST_ASSERT_EQUAL(list->length, 2);
	FEUR_TEST_ASSERT_EQUAL(array_list_is_empty(list), false);

	int out;
	array_list_pop_int(list, &out);
	FEUR_TEST_ASSERT_EQUAL(out, 20);
	FEUR_TEST_ASSERT_EQUAL(list->length, 1);

	array_list_pop_int(list, &out);
	FEUR_TEST_ASSERT_EQUAL(out, 10);
	FEUR_TEST_ASSERT_EQUAL(list->length, 0);
	FEUR_TEST_ASSERT_EQUAL(array_list_is_empty(list), true);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Get_Int()
{
	ArrayList* list = array_list_create(sizeof(int), 2);
	int a = 42;

	array_list_push(list, &a);

	int out = 0;
	array_list_get_int(list, 0, &out);
	FEUR_TEST_ASSERT_EQUAL(out, 42);

	int* ptr = (int*)array_list_get(list, 0);
	FEUR_TEST_ASSERT_EQUAL(*ptr, 42);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Clear()
{
	ArrayList* list = array_list_create(sizeof(int), 2);
	int a = 1;

	array_list_push(list, &a);
	array_list_push(list, &a);
	array_list_clear(list);

	FEUR_TEST_ASSERT_EQUAL(list->length, 0);
	FEUR_TEST_ASSERT_EQUAL(array_list_is_empty(list), true);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Push_Buffer()
{
	ArrayList* list = array_list_create(sizeof(int), 2);
	int arr[3] = {100, 200, 300};

	array_list_push_buffer(list, arr, 3);

	FEUR_TEST_ASSERT_EQUAL(list->length, 3);

	int out;
	array_list_get_int(list, 1, &out);
	FEUR_TEST_ASSERT_EQUAL(out, 200);

	array_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Copy()
{
	ArrayList* src = array_list_create(sizeof(int), 2);
	int a = 5;
	array_list_push(src, &a);

	ArrayList* dest = array_list_create(sizeof(int), 1);
	array_list_copy(src, dest);

	FEUR_TEST_ASSERT_EQUAL(dest->length, 1);
	
	int out;
	array_list_get_int(dest, 0, &out);
	FEUR_TEST_ASSERT_EQUAL(out, 5);

	array_list_free(src);
	array_list_free(dest);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Push_Array()
{
	ArrayList* list1 = array_list_create(sizeof(int), 2);
	ArrayList* list2 = array_list_create(sizeof(int), 2);
	int a = 7;
	
	array_list_push(list2, &a);
	array_list_push_array(list1, list2);

	FEUR_TEST_ASSERT_EQUAL(list1->length, 1);

	int out;
	array_list_get_int(list1, 0, &out);
	FEUR_TEST_ASSERT_EQUAL(out, 7);

	array_list_free(list1);
	array_list_free(list2);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ArrayList_Resize_Reserve()
{
	ArrayList* list = array_list_create(sizeof(int), 2);
	
	array_list_resize(list, 5);
	FEUR_TEST_ASSERT_EQUAL(list->capacity, 5);

	int items[5] = { 1, 2, 3, 4, 5 };

	array_list_push_buffer(list, items, 5);

	array_list_reserve(list, 5);
	
	FEUR_TEST_ASSERT_EQUAL(list->capacity >= 10, true);

	array_list_free(list);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("Lifecycle");
	FEUR_Test_Add_Test("Create Free", Test_ArrayList_Create_Free);
	FEUR_Test_Add_Test("Clear", Test_ArrayList_Clear);

	FEUR_Test_Add_Group("Modifiers");
	FEUR_Test_Add_Test("Push Pop Int", Test_ArrayList_Push_Pop_Int);
	FEUR_Test_Add_Test("Push Buffer", Test_ArrayList_Push_Buffer);
	FEUR_Test_Add_Test("Push Array", Test_ArrayList_Push_Array);
	FEUR_Test_Add_Test("Resize Reserve", Test_ArrayList_Resize_Reserve);

	FEUR_Test_Add_Group("Accessors");
	FEUR_Test_Add_Test("Get Int", Test_ArrayList_Get_Int);

	FEUR_Test_Add_Group("Utilities");
	FEUR_Test_Add_Test("Copy", Test_ArrayList_Copy);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}

