#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LIST_ITERATOR_H

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
void linked_list_iterator_init_copy(LinkedListIterator* iterator, LinkedListIterator* source);

bool linked_list_iterator_go_next(LinkedListIterator* iterator);
bool linked_list_iterator_go_previous(LinkedListIterator* iterator);

void linked_list_iterator_go_begin(LinkedListIterator* iterator);
void linked_list_iterator_go_end(LinkedListIterator* iterator);

void linked_list_iterator_go_to(LinkedListIterator* iterator, size_t index);

LinkedListNode* linked_list_iterator_get_node(LinkedListIterator* iterator);

void* linked_list_iterator_get_data(LinkedListIterator* iterator);

size_t linked_list_iterator_get_index(LinkedListIterator* iterator);

#endif // LINKED_LIST_ITERATOR_H
