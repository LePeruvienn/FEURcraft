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

bool linked_list_iterator_go_next(LinkedListIterator* iterator)
{
    CHECK_IS_NULL_RET(iterator, "Cannot go next a NULL LinkedListIterator", );

    if (iterator->current_node == NULL)
    {
        LOG_WARNING("LinkedListIterator current node is NULL");
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

void linked_list_iterator_rewind(LinkedListIterator* iterator)
{
    CHECK_IS_NULL_RET(iterator, "Cannot rewind a NULL LinkedListIterator", );

    iterator->current_node = iterator->list->root_node;
    iterator->current_index = 0;
}

LinkedListNode* linked_list_iterator_get_node(LinkedListIterator* iterator)
{
    CHECK_IS_NULL_RET(iterator, "Cannot get data from a NULL LinkedListIterator", );

    return iterator->current_node;
}

void* linked_list_iterator_get_data(LinkedListIterator* iterator)
{
    CHECK_IS_NULL_RET(iterator, "Cannot get data from a NULL LinkedListIterator", );

    if (iterator->current_node == NULL)
    {
        return NULL;
    }
    
    return iterator->current_node->data;
}

size_t linked_list_iterator_get_index(LinkedListIterator* iterator)
{
    CHECK_IS_NULL_RET(iterator, "Cannot get index from a NULL LinkedListIterator", );

    return iterator->current_index;
}
