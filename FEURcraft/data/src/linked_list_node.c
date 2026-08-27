#include "linked_list_node.h"

#include "error_checker.h"
#include "logger.h"
#include "ptr_helper.h"

#include <stdlib.h>
#include <string.h>

static LinkedListNode*  linked_list_node_create_default(size_t size)
{
	LinkedListNode* node = malloc(sizeof(struct LinkedListNode));

	CHECK_IS_NULL_RET(node, "Failed to malloc LinkedListNode.", NULL);

	node->previous = NULL;
	node->next = NULL;

	node->data = malloc(size);
	node->size = size;

	if(node->data == NULL)
	{
		LOG_ERROR("Failed to malloc LinkedListNode data.");
		free(node);
		return NULL;
	}

	return node;
}

LinkedListNode* linked_list_node_create(void* data, size_t size)
{
	CHECK_IS_NULL_RET(data, "Cannot create LinkedListNode with NULL data", NULL);

	LinkedListNode* node = linked_list_node_create_default(size);

	CHECK_IS_NULL_RET(node, "Failed to create LinkedListNode", NULL);

	// copy the data to the node
	memcpy(node->data, data, size);

	return node;
}

LinkedListNode* linked_list_node_create_empty(size_t size)
{
	LinkedListNode* node = linked_list_node_create_default(size);

	CHECK_IS_NULL_RET(node, "Failed to create LinkedListNode", NULL);

	// setting the data to 0
	memset(node->data, 0, size);

	return node;
}

void linked_list_node_free(LinkedListNode* node)
{
	CHECK_IS_NULL_RET(node, "Cannot free NULL LinkedListNode.", );
	FREE_PTR_NOT_NULL(node->data, free);
	free(node);
}

void linked_list_node_set_data(LinkedListNode* node, void* data)
{
	CHECK_IS_NULL_RET(node, "Cannot set data of a NULL LinkedListNode.", );
	CHECK_IS_NULL_RET(data, "Cannot set NULL data to a  LinkedListNode", );

	memcpy(node->data, data, node->size);
}
