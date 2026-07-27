#include "array_list.h"

#include "error_checker.h"
#include "logger.h"
#include "ptr_helper.h"

#include <stdlib.h>
#include <string.h>

ArrayList* array_list_create(size_t item_size, size_t capacity)
{
	CHECK_COND_RET(capacity > 0,
		"Initila ArrayList capacity cannot be 0.", NULL);

	ArrayList* list = malloc(sizeof(struct ArrayList));

	CHECK_IS_NULL_RET(list, "Failed ArrayList malloc.", NULL);

	list->data = NULL;

	list->item_size = item_size;

	list->count = 0;
	list->capacity = capacity;

	array_list_resize(list, capacity);

	if (list->data == NULL)
	{
		LOG_ERROR("Failed to reserve memory of ArrayList");
		array_list_free(list);
		return NULL;
	}

	return list;
}

void array_list_free(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot free a NULL ArrayList.", );

	FREE_PTR_NOT_NULL(list->data, free);

	free(list);
}

void array_list_resize(ArrayList* list, size_t new_capacity)
{
	CHECK_IS_NULL_RET(list, "Cannot reserve a NULL ArrayList.", );

	CHECK_COND_RET(list->count <= new_capacity,
		"Cannot resize less than actual ArrayList count.", );

	size_t new_data_size = list->item_size * new_capacity;

	unsigned char* new_data = NULL;

	// realloc se comporte comme un malloc si list->data NULL.
	new_data = realloc(list->data, new_data_size);

	if (new_data == NULL)
	{
		LOG_ERROR("Failed to alloc %zu bytes to ArrayList.", new_data_size);
		return;
	}

	list->data = new_data;
	list->capacity = new_capacity;
}

void array_list_reserve(ArrayList* list, size_t capacity)
{
	CHECK_IS_NULL_RET(list, "Cannot reserve a NULL ArrayList.", );

	CHECK_COND_RET_WARN(capacity > 0,
		"ArrayList list reseve(0) have no impact.", );

	array_list_resize(list, list->capacity + capacity);
}

static void* array_list_get_unsafe(ArrayList* list, size_t index)
{
	// D'après la norm C, unsigned char fait toujours 1 octet.
	return ((unsigned char*) list->data) + (index * list->item_size);
}

void* array_list_get(ArrayList* list, size_t index)
{
	CHECK_COND_RET(index < list->count, "Invalid Array List Index.", NULL);

	// D'après la norm C, unsigned char fait toujours 1 octet.
	return array_list_get_unsafe(list, index);
}

void array_list_push(ArrayList* list, void* item)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", );
	CHECK_IS_NULL_RET(item, "Cannot push a NULL item to ArrayList.", );

	if (list->count >= list->capacity)
	{
		CHECK_COND_WARN(list->count > list->capacity,
			"ArrayList count was more than his capacity.");

		array_list_reserve(list, list->capacity);
	}

	unsigned char* dest = array_list_get_unsafe(list, list->count);

	memcpy(dest, item, list->item_size);

	++list->count;
}

void array_list_clear(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot clear a NULL ArrayList.", );

	list->count = 0;
}

