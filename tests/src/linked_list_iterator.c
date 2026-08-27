#include "FEUR_Test/FEUR_Test.h"
#include "linked_list_iterator.h"
#include "linked_list.h"

FEUR_Test_Result Test_Iterator_Init()
{
	LinkedList* list = linked_list_create(sizeof(int));
	int v = 5;
	linked_list_push_back_copy(list, &v);

	LinkedListIterator it;
	linked_list_iterator_init(&it, list);

	FEUR_TEST_ASSERT(it.list == list);
	FEUR_TEST_ASSERT(it.current_index == 0);
	FEUR_TEST_ASSERT(it.current_node == list->root_node);
	FEUR_TEST_ASSERT(*(int*)linked_list_iterator_get_data(&it) == 5);

	linked_list_free(list);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Iterator_Navigation()
{
	LinkedList* list = linked_list_create(sizeof(int));
	int v1 = 1, v2 = 2, v3 = 3;
	linked_list_push_back_copy(list, &v1);
	linked_list_push_back_copy(list, &v2);
	linked_list_push_back_copy(list, &v3);

	LinkedListIterator it;
	linked_list_iterator_init(&it, list);

	// Go next
	FEUR_TEST_ASSERT(linked_list_iterator_go_next(&it) == true);
	FEUR_TEST_ASSERT(linked_list_iterator_get_index(&it) == 1);
	FEUR_TEST_ASSERT(*(int*)linked_list_iterator_get_data(&it) == 2);

	// Go previous
	FEUR_TEST_ASSERT(linked_list_iterator_go_previous(&it) == true);
	FEUR_TEST_ASSERT(linked_list_iterator_get_index(&it) == 0);
	
	// Edge cases : Dépasser les limites
	FEUR_TEST_ASSERT(linked_list_iterator_go_previous(&it) == false); // Deja au debut
	
	linked_list_iterator_go_end(&it);
	FEUR_TEST_ASSERT(linked_list_iterator_go_next(&it) == false); // Deja a la fin

	linked_list_free(list);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Iterator_GoTo()
{
	LinkedList* list = linked_list_create(sizeof(int));
	int v1 = 10, v2 = 20, v3 = 30;
	linked_list_push_back_copy(list, &v1);
	linked_list_push_back_copy(list, &v2);
	linked_list_push_back_copy(list, &v3);

	LinkedListIterator it;
	linked_list_iterator_init(&it, list);

	// Go to valide (avance)
	linked_list_iterator_go_to(&it, 2);
	FEUR_TEST_ASSERT(*(int*) linked_list_iterator_get_data(&it) == 30);

	// Go to valide (recule)
	linked_list_iterator_go_to(&it, 0);
	FEUR_TEST_ASSERT(*(int*) linked_list_iterator_get_data(&it) == 10);

	// Edge case : Go to invalide (ne doit rien faire, l'index reste 0)
	// linked_list_iterator_go_to(&it, 99);
	// FEUR_TEST_ASSERT(linked_list_iterator_get_index(&it) == 0);

	linked_list_free(list);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Iterator_EmptyList()
{
	LinkedList* list = linked_list_create(sizeof(int));
	LinkedListIterator it;
	
	linked_list_iterator_init(&it, list);
	
	// Edge cases critiques sur liste vide
	FEUR_TEST_ASSERT(linked_list_iterator_get_data(&it) == NULL);
	FEUR_TEST_ASSERT(linked_list_iterator_go_next(&it) == false);
	
	// Ce test risque de crasher ton programme à cause du bug de `go_end` (0 - 1 = SIZE_MAX)
	// C'est exactement l'utilité de l'avoir en test unitaire !
	linked_list_iterator_go_end(&it);
	
	linked_list_free(list);
	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("LinkedListIterator - Init");
	FEUR_Test_Add_Test("Initialisation", Test_Iterator_Init);

	FEUR_Test_Add_Group("LinkedListIterator - Navigation");
	FEUR_Test_Add_Test("Next / Previous et Limites", Test_Iterator_Navigation);
	FEUR_Test_Add_Test("Go To (saut d'index)", Test_Iterator_GoTo);
	FEUR_Test_Add_Test("Edge Cases (Liste Vide)", Test_Iterator_EmptyList);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
