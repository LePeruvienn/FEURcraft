#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "linked_list_node.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct LinkedList LinkedList;

struct LinkedList
{
	size_t item_size;
	size_t length;

	LinkedListNode* root_node;
	LinkedListNode* tail_node;
};

LinkedList* linked_list_create(size_t item_size);

void linked_list_free(LinkedList* list);

bool linked_list_push_back(LinkedList* list, void* item);
bool linked_list_push_front(LinkedList* list, void* item);

bool linked_list_pop(LinkedList* list, void* out);
bool linked_list_shift(LinkedList* list, void* out);

void* linked_list_get_data(LinkedList* list, size_t index);

#endif // LINKED_LIST_H
