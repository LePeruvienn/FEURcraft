#include "linked_list.h"
#include "linked_list_node.h"
#include "linked_list_iterator.h"

#include "error_checker.h"
#include "logger.h"

#include <stdlib.h>
#include <string.h>

LinkedList* linked_list_create(size_t item_size)
{
	LinkedList* list = malloc(sizeof(struct LinkedList));

	CHECK_IS_NULL_RET(list, "Failed to malloc LinkedList", NULL);

	list->item_size = item_size;
	list->length = 0;
	list->root_node = NULL;
	list->tail_node = NULL;
	
	return list;
}

void linked_list_free(LinkedList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot free a NULL LinkedList", );
	
	if (list->root_node == NULL && list->tail_node == NULL)
	{
		free(list);
		return;
	}

	while(list->root_node != NULL)
	{
		LinkedListNode* node = list->root_node;
		list->root_node = node->next;
		linked_list_node_free(node);
	}

	free(list);
}

bool linked_list_push_back(LinkedList* list, void* item)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL LinkedList", false);
	CHECK_IS_NULL_RET(item, "Cannot push a NULL item to LinkedList", false);

	LinkedListNode* new_node = linked_list_node_create(item, list->item_size);
	CHECK_IS_NULL_RET(new_node, "Failed to create new LinkedListNode", false);

	++list->length;

	if (list->root_node == NULL)
	{
		list->root_node = new_node;
		list->tail_node = new_node;
		return true;
	}

	list->tail_node->next = new_node;
	new_node->previous = list->tail_node;
	list->tail_node = new_node;

	return true;
}

bool linked_list_push_front(LinkedList* list, void* item)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL LinkedList", false);
	CHECK_IS_NULL_RET(item, "Cannot push a NULL item to LinkedList", false);

	LinkedListNode* new_node = linked_list_node_create(item, list->item_size);
	CHECK_IS_NULL_RET(new_node, "Failed to create new LinkedListNode", false);

	++list->length;

	if (list->root_node == NULL)
	{
		list->root_node = new_node;
		list->tail_node = new_node;
		return true;
	}

	list->root_node->previous = new_node;
	new_node->next = list->root_node;
	list->root_node = new_node;

	return true;
}

bool linked_list_pop(LinkedList* list, void* out)
{
	CHECK_IS_NULL_RET(list, "Cannot pop a NULL LinkedList", false);
	CHECK_IS_NULL_RET(out, "Cannot pop LinkedList to a NULL ptr", false);

	if (list->tail_node == NULL)
	{
		CHECK_COND_RET(list->root_node == NULL, "tail_node is NULL but not root_node ???", false);
		return false;
	}

	CHECK_IS_NULL_RET(list->tail_node->data, "Tail node not data is NULL this should not happen", false);

	memcpy(out, list->tail_node->data, list->item_size);

	--list->length;

	if (list->tail_node == list->root_node)
	{
		linked_list_node_free(list->tail_node);

		list->root_node = NULL;
		list->tail_node = NULL;

		return true;
	}

	LinkedListNode* old_tail = list->tail_node;

	list->tail_node = old_tail->previous;
	list->tail_node->next = NULL;

	linked_list_node_free(old_tail);

	return true;
}

bool linked_list_shift(LinkedList* list, void* out)
{
	CHECK_IS_NULL_RET(list, "Cannot shift a NULL LinkedList", false);
	CHECK_IS_NULL_RET(out, "Cannot shift LinkedList to a NULL ptr", false);

	if (list->root_node == NULL)
	{
		CHECK_COND_RET(list->tail_node == NULL, "tail_node is NULL but not root_node ???", false);
		return false;
	}

	CHECK_IS_NULL_RET(list->root_node->data, "Root node not data is NULL this should not happen", false);

	memcpy(out, list->root_node->data, list->item_size);

	--list->length;

	if (list->tail_node == list->root_node)
	{
		linked_list_node_free(list->root_node);

		list->root_node = NULL;
		list->tail_node = NULL;

		return true;
	}

	LinkedListNode* old_root = list->root_node;

	list->root_node = old_root->next;
	list->root_node->previous = NULL;

	linked_list_node_free(old_root);

	return true;
}

void* linked_list_get_data(LinkedList* list, size_t index)
{
	CHECK_IS_NULL_RET(list, "Cannot get data from a NULL LinkedList", NULL);

	CHECK_COND_RET(index < list->length,
		"Cannot get LinkedList data from an invalid index", NULL);

	LinkedListIterator iterator;
	linked_list_iterator_init(&iterator, list);

	if (index < list->length / 2)
	{
		linked_list_iterator_go_begin(&iterator);
	}
	else
	{
		linked_list_iterator_go_end(&iterator);
	}

	linked_list_iterator_go_to(&iterator, index);

	return linked_list_iterator_get_data(&iterator);
}

