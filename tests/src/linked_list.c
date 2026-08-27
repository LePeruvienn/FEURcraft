#include "FEUR_Test/FEUR_Test.h"
#include "linked_list.h"

FEUR_Test_Result Test_LinkedList_Create()
{
	LinkedList* list = linked_list_create(sizeof(int));

	FEUR_TEST_ASSERT_NOT_NULL(list);
	FEUR_TEST_ASSERT(list->item_size == sizeof(int));
	FEUR_TEST_ASSERT(list->length == 0);
	FEUR_TEST_ASSERT(list->root_node == NULL);
	FEUR_TEST_ASSERT(list->tail_node == NULL);

	linked_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_LinkedList_Push()
{
	LinkedList* list = linked_list_create(sizeof(int));
	int v1 = 1, v2 = 2, v3 = 3;

	// Push Back sur liste vide
	FEUR_TEST_ASSERT(linked_list_push_back_copy(list, &v1) == true);
	FEUR_TEST_ASSERT(list->length == 1);
	FEUR_TEST_ASSERT(list->root_node == list->tail_node);

	// Push Front
	FEUR_TEST_ASSERT(linked_list_push_front_copy(list, &v2) == true);
	FEUR_TEST_ASSERT(list->length == 2);
	FEUR_TEST_ASSERT(*(int*)list->root_node->data == 2);

	linked_list_free(list);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_LinkedList_PopAndShift()
{
	LinkedList* list = linked_list_create(sizeof(int));
	int v1 = 10, v2 = 20;
	linked_list_push_back_copy(list, &v1);
	linked_list_push_back_copy(list, &v2);

	int out;
	
	// Pop normal
	FEUR_TEST_ASSERT(linked_list_pop(list, &out) == true);
	FEUR_TEST_ASSERT(out == 20);
	FEUR_TEST_ASSERT(list->length == 1);

	// Shift (retire le dernier restant qui est aussi la racine)
	FEUR_TEST_ASSERT(linked_list_shift(list, &out) == true);
	FEUR_TEST_ASSERT(out == 10);
	FEUR_TEST_ASSERT(list->length == 0);
	FEUR_TEST_ASSERT(list->root_node == NULL);
	FEUR_TEST_ASSERT(list->tail_node == NULL);

	// Edge case : Pop/Shift sur liste vide
	FEUR_TEST_ASSERT(linked_list_pop(list, &out) == false);
	FEUR_TEST_ASSERT(linked_list_shift(list, &out) == false);

	linked_list_free(list);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_LinkedList_GetData()
{
	LinkedList* list = linked_list_create(sizeof(int));

	int v1 = 100, v2 = 200, v3 = 300;

	linked_list_push_back_copy(list, &v1);
	linked_list_push_back_copy(list, &v2);
	linked_list_push_back_copy(list, &v3);

	FEUR_TEST_ASSERT(* (int*) linked_list_get(list, 0) == 100);
	FEUR_TEST_ASSERT(* (int*) linked_list_get(list, 1) == 200);
	FEUR_TEST_ASSERT(* (int*) linked_list_get(list, 2) == 300);

	linked_list_free(list);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("LinkedList - Creation");
	FEUR_Test_Add_Test("Creation basique", Test_LinkedList_Create);

	FEUR_Test_Add_Group("LinkedList - Manipulation");
	FEUR_Test_Add_Test("Push Front/Back", Test_LinkedList_Push);
	FEUR_Test_Add_Test("Pop et Shift", Test_LinkedList_PopAndShift);
	FEUR_Test_Add_Test("Get Data (Acces par index)", Test_LinkedList_GetData);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}

