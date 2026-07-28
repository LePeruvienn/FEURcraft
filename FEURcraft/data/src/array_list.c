#include "array_list.h"

#include "error_checker.h"
#include "logger.h"
#include "ptr_helper.h"

#include <stdlib.h>
#include <string.h>

#define ARRAY_LIST_DEFAULT_CAPACITY 8

ArrayList* array_list_create(size_t item_size, size_t capacity)
{
	ArrayList* list = malloc(sizeof(struct ArrayList));

	CHECK_IS_NULL_RET(list, "Failed ArrayList malloc.", NULL);

	// when you allocate data it's not a static ArrayList
	list->is_static = false;

	list->data = NULL;

	list->item_size = item_size;

	list->count = 0;
	list->capacity = capacity;

	if (capacity == 0)
	{
		return list;
	}

	array_list_resize(list, capacity);

	if (list->data == NULL)
	{
		LOG_ERROR("Failed to reserve memory of ArrayList");
		array_list_free(list);
		return NULL;
	}

	return list;
}

void array_list_copy(const ArrayList* source, ArrayList* dest)
{
	CHECK_IS_NULL_RET(source, "Cannot copy from a NULL ArrayList.", );
	CHECK_IS_NULL_RET(dest, "Cannot copy to a NULL ArrayList.", );

	CHECK_COND_RET(source->item_size == dest->item_size,
		"Cant copy array list to item that is not the same size.", );

	if (source->count > dest->capacity)
	{
		CHECK_COND_RET(dest->is_static == false,
			"Cannot copy: destination is a static ArrayList and capacity is too small.", );

		array_list_reserve(dest, source->count - dest->capacity);
	}

	dest->count = source->count;

	CHECK_COND_RET_WARN(dest->count > 0,
		"Tried to copy a empty ArrayList.", );

	memcpy(dest->data, source->data, source->count * source->item_size);
}

void array_list_free(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot free a NULL ArrayList.", );
	CHECK_COND_RET(list->is_static == false, "Cannot free a static ArrayList.", );

	FREE_PTR_NOT_NULL(list->data, free);

	free(list);
}

void array_list_resize(ArrayList* list, size_t new_capacity)
{
	CHECK_IS_NULL_RET(list, "Cannot resize a NULL ArrayList.", );
	CHECK_COND_RET(list->is_static == false, "Cannot resize a static ArrayList.", );

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
	CHECK_COND_RET(list->is_static == false, "Cannot reserve a static ArrayList.", );

	CHECK_COND_RET_WARN(capacity > 0,
		"ArrayList list reseve(0) have no impact.", );

	array_list_resize(list, list->capacity + capacity);
}

static void* array_list_get_unsafe(const ArrayList* list, size_t index)
{
	// D'après la norm C, unsigned char fait toujours 1 octet.
	return ((unsigned char*) list->data) + (index * list->item_size);
}

void* array_list_get(const ArrayList* list, size_t index)
{
	CHECK_COND_RET(index < list->count, "Invalid Array List Index.", NULL);

	// D'après la norm C, unsigned char fait toujours 1 octet.
	return array_list_get_unsafe(list, index);
}

void array_list_push(ArrayList* list, const void* item)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", );
	CHECK_IS_NULL_RET(item, "Cannot push a NULL item to ArrayList.", );

	if (list->count >= list->capacity)
	{
		CHECK_COND_WARN(list->count > list->capacity,
			"ArrayList count was more than his capacity.");

		CHECK_COND_RET(list->is_static == false,
			"Cannot push more data to a static ArrayList.", );

		size_t capacity_to_reserve = (list->capacity == 0) ?
			ARRAY_LIST_DEFAULT_CAPACITY : list->capacity;

		array_list_reserve(list, capacity_to_reserve);
	}

	unsigned char* dest = array_list_get_unsafe(list, list->count);

	memcpy(dest, item, list->item_size);

	++list->count;
}

void array_list_push_buffer(ArrayList* list, const void* items, size_t items_len)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", );
	CHECK_IS_NULL_RET(items, "Cannot push a NULL items ptr to ArrayList.", );
	
	size_t capacity_needed = (list->capacity == 0) ?
		ARRAY_LIST_DEFAULT_CAPACITY : list->capacity;

	while(list->count + items_len > capacity_needed)
	{
		capacity_needed += capacity_needed;
	}

	size_t capacity_to_reserve = capacity_needed - list->capacity;

	if (capacity_to_reserve > 0)
	{
		CHECK_COND_RET(list->is_static == false,
			"Cannot push more data to a static ArrayList.", );

		array_list_reserve(list, capacity_to_reserve);
	}

	unsigned char* dest = array_list_get_unsafe(list, list->count);

	memcpy(dest, items, list->item_size * items_len);

	list->count += items_len;
}

void array_list_push_array(ArrayList* list, const ArrayList* list_to_add)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", );
	CHECK_IS_NULL_RET(list_to_add, "Cannot push a NULL ArrayList to ArrayList.", );

	CHECK_COND_RET(list != list_to_add,
		"Cannot push ArrayList to himself.", );

	CHECK_COND_RET(list->data != list_to_add->data,
		"Cannot both ArrayList have the same buffer ??", );

	CHECK_COND_RET(list->item_size == list_to_add->item_size,
		"Cannot push ArrayList with different item_size.", );

	CHECK_COND_RET_WARN(list_to_add->count > 0,
		"Trying to add to ArrayList an ArrayList of count = 0.", );

	CHECK_COND_RET_WARN(list_to_add->data != NULL,
		"ArrayList that is adding have a NULL data but count > 0 ???", );

	array_list_push_buffer(list, list_to_add->data, list_to_add->count);
}

void array_list_clear(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot clear a NULL ArrayList.", );

	list->count = 0;
}

