#include "FEUR_Test/FEUR_Test.h"

#include "linked_list_node.h"
#include <string.h>

FEUR_Test_Result Test_LinkedListNode_Create()
{
	int data = 42;
	LinkedListNode* node = linked_list_node_create(&data, sizeof(int));

	FEUR_TEST_ASSERT_NOT_NULL(node);
	FEUR_TEST_ASSERT_NOT_NULL(node->data);
	FEUR_TEST_ASSERT(node->size == sizeof(int));
	FEUR_TEST_ASSERT(*(int*)node->data == 42);
	FEUR_TEST_ASSERT(node->next == NULL);
	FEUR_TEST_ASSERT(node->previous == NULL);

	linked_list_node_free(node);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_LinkedListNode_SetData()
{
	int data1 = 10;
	LinkedListNode* node = linked_list_node_create(&data1, sizeof(int));
	
	int data2 = 99;
	linked_list_node_set_data(node, &data2);
	FEUR_TEST_ASSERT(*(int*)node->data == 99);

	linked_list_node_free(node);
	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("LinkedListNode - Creation");
	FEUR_Test_Add_Test("Creation basique", Test_LinkedListNode_Create);

	FEUR_Test_Add_Group("LinkedListNode - Manipulation");
	FEUR_Test_Add_Test("Set data", Test_LinkedListNode_SetData);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
