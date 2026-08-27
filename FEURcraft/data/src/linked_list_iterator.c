#include "linked_list_iterator.h"
#include "linked_list.h"

#include "error_checker.h"
#include "logger.h"

#include <stdbool.h>

void linked_list_iterator_init(LinkedListIterator* iterator, LinkedList* list)
{
	CHECK_IS_NULL_RET(iterator, "Cannot init a NULL LinkedListIterator", );
	CHECK_IS_NULL_RET(list, "Cannot init a LinkedListIterator with a NULL LinkedList", );

	iterator->list = list;
	iterator->current_node = list->root_node;
	iterator->current_index = 0;
}

void linked_list_iterator_init_copy(LinkedListIterator* iterator, LinkedListIterator* source)
{
	CHECK_IS_NULL_RET(iterator, "cannot init copy from a NULL LinkedListIterator", );
	CHECK_IS_NULL_RET(source, "cannot init copy from a NULL source  LinkedListIterator", );

	iterator->list = source->list;
	iterator->current_node = source->current_node;
	iterator->current_index = source->current_index;
}

bool linked_list_iterator_go_next(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot go next of a NULL LinkedListIterator", false);

	if (iterator->current_node == NULL)
	{
		// LOG_WARNING("LinkedListIterator current node is NULL");
		return false;
	}

	if (iterator->current_node->next == NULL)
	{
		return false;
	}

	iterator->current_node = iterator->current_node->next;
	++iterator->current_index;

	return true;
}

bool linked_list_iterator_go_previous(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot go previous of a NULL LinkedListIterator", false);

	if (iterator->current_node == NULL)
	{
		// LOG_WARNING("LinkedListIterator current node is NULL");
		return false;
	}

	if (iterator->current_node->previous == NULL)
	{
		return false;
	}

	iterator->current_node = iterator->current_node->previous;
	--iterator->current_index;

	return true;
}

void linked_list_iterator_go_begin(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot use go begin with a NULL LinkedListIterator", );
	CHECK_IS_NULL_RET(iterator->list, "LinkedList of Iterator is NULL", );

	iterator->current_node = iterator->list->root_node;
	iterator->current_index = 0;
}

void linked_list_iterator_go_end(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot use go begin with a NULL LinkedListIterator", );
	CHECK_IS_NULL_RET(iterator->list, "LinkedList of Iterator is NULL", );

	if (iterator->list->length == 0)
	{
		LOG_WARNING("Going at the end of a empty LinkedList");
		return;
	}

	iterator->current_node = iterator->list->tail_node;
	iterator->current_index = iterator->list->length - 1;
}

void linked_list_iterator_go_to(LinkedListIterator* iterator, size_t index)
{
	CHECK_IS_NULL_RET(iterator, "Cannot goto with a NULL LinkedListIterator", );

	CHECK_COND_RET(iterator->list->length > index,
		"LinkedListIterator cannot go to an invalid index", );

	if (iterator->current_index == index)
	{
		return;
	}

	while(iterator->current_index != index)
	{
		if (index > iterator->current_index)
		{
			if(linked_list_iterator_go_next(iterator) == false)
			{
				LOG_ERROR("Failed to go to the location desired");
				break;
			}
		}
		else
		{
			if(linked_list_iterator_go_previous(iterator) == false)
			{
				LOG_ERROR("Failed to go to the location desired");
				break;
			}
		}
	}
}

LinkedListNode* linked_list_iterator_get_node(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot get data from a NULL LinkedListIterator", NULL);

	return iterator->current_node;
}

void* linked_list_iterator_get_data(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot get data from a NULL LinkedListIterator", NULL);

	if (iterator->current_node == NULL)
	{
		return NULL;
	}
	
	return iterator->current_node->data;
}

size_t linked_list_iterator_get_index(LinkedListIterator* iterator)
{
	CHECK_IS_NULL_RET(iterator, "Cannot get index from a NULL LinkedListIterator", 0);

	return iterator->current_index;
}

