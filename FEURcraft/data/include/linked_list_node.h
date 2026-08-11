#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#include <stddef.h>

typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode
{
	void* data;
	size_t size;

	LinkedListNode* next;
	LinkedListNode* previous;
};

LinkedListNode* linked_list_node_create(void* data, size_t size);

void linked_list_node_free(LinkedListNode* node);

void linked_list_node_set_data(LinkedListNode* node, void* data);

#endif // LINKED_LIST_NODE_H
