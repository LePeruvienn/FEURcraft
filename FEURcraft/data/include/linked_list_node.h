#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#include <stddef.h>

typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode
{
    void* data;
    size_t item_size;

    LinkedListNode* next;
    LinkedListNode* previous;
};

LinkedListNode* linked_list_node_create(size_t item_size);

void linked_list_node_free(LinkedListNode* node);

void* linked_list_node_get_data(LinkedListNode* node);

LinkedListNode* linked_list_node_get_next(LinkedListNode* node);

void linked_list_node_set_data(LinkedListNode* node, void* data);

void linked_list_node_set_next(LinkedListNode* node, LinkedListNode* next);


#endif // LINKED_LIST_NODE_H