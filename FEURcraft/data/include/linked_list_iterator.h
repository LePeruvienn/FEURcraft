#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LISt_ITERATOR_H

#include "linked_list.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct LinkedListIterator LinkedListIterator;

struct LinkedListIterator
{
    LinkedList* list;
    LinkedListNode* current_node;

    size_t current_index;
};

void linked_list_iterator_init(LinkedListIterator* iterator, LinkedList* list);

bool linked_list_iterator_go_next(LinkedListIterator* iterator);

void linked_list_iterator_rewind(LinkedListIterator* iterator);

LinkedListNode* linked_list_iterator_get_node(LinkedListIterator* iterator);

void* linked_list_iterator_get_data(LinkedListIterator* iterator);

size_t linked_list_iterator_get_index(LinkedListIterator* iterator);

#endif // LINKED_LIST_ITERATOR_H