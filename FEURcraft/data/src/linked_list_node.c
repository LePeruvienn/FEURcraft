#include "linked_list_node.h"

#include "error_checker.h"
#include "ptr_helper.h"

#include <stdlib.h>
#include <string.h>

LinkedListNode* linked_list_node_create(size_t item_size)
{
    LinkedListNode* node = malloc(sizeof(struct LinkedListNode)) ;

    CHECK_IS_NULL_RET(node, "Faile to malloc LinkedListNode", NULL);

    node->item_size = item_size;
    node->data = NULL;
    node->next = NULL;

    return node;
}

void linked_list_node_free(LinkedListNode* node)
{
    FREE_PTR_NOT_NULL(node->data, free);
    free(node);
}

void* linked_list_node_get_data(LinkedListNode* node)
{
    return node->data;
}

LinkedListNode* linked_list_node_get_next(LinkedListNode* node)
{
    return node->next;
}

void linked_list_node_set_data(LinkedListNode* node, void* data)
{
    if (node->data == NULL)
    {
        void* data = malloc(node->item_size);
        CHECK_IS_NULL_RET(data, "Failed to malloc LinkedListNode data", );
        node->data = data;
    }

    memcpy(node->data, data, node->item_size);
}

void linked_list_node_set_next(LinkedListNode* node, LinkedListNode* next)
{
    node->next = next;
}
