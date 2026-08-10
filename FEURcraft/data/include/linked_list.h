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

bool linked_list_push(LinkedList* list, void* item);

bool linked_list_shift(LinkedList* list, void* out);

void linked_list_free(LinkedList* list);

#endif // LINKED_LIST_H