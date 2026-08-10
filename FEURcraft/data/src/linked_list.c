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

bool linked_list_push(LinkedList* list, void* item)
{
    CHECK_IS_NULL_RET(list, "Cannot push to a NULL LinkedList", false);
    CHECK_IS_NULL_RET(item, "Cannot push a NULL item to LinkedList", false);

    if (list->root_node == NULL)
    {
        list->root_node = linked_list_node_create(list->item_size);
    }

    LinkedListIterator iterator;
    linked_list_iterator_init(&iterator, list);

    while(linked_list_iterator_get_data(&iterator) != NULL)
    {
        linked_list_iterator_go_next(&iterator);
    }

    LinkedListNode* node = linked_list_iterator_get_node(&iterator);

    CHECK_PTR_NOT_NULL_RET(node,
        "LinkedListIterator has gone too far, current node is NULL", false);

    node->next = linked_list_node_create(list->item_size);

    CHECK_PTR_NOT_NULL_RET(node->next,
        "Failed to create next node", false);

    linked_list_node_set_data(node->next, item);

    ++list->length;

    return true;
}

bool linked_list_shift(LinkedList* list, void* out)
{
    CHECK_COND_RET(list->length > 0, "Cannot shift a empty LinkedList", false);
    CHECK_IS_NULL_RET(list->root_node, "LinkedList root node is NULL", false);
    CHECK_IS_NULL_RET(list->root_node->data, "LinkedList root node data is NULL", false);

    memcpy(out, list->root_node->data, list->item_size);

    return true;
}

void linked_list_free(LinkedList* list)
{
    LinkedListIterator iterator;
    linked_list_iterator_init(&iterator, list);

    while(linked_list_iterator_get_data(&iterator) != NULL)
    {
        linked_list_iterator_go_next(&iterator);
    }
}
