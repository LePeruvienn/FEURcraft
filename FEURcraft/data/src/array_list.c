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

	list->length = 0;
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

bool array_list_copy(const ArrayList* source, ArrayList* dest)
{
	CHECK_IS_NULL_RET(source, "Cannot copy from a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(dest, "Cannot copy to a NULL ArrayList.", false);

	CHECK_COND_RET(source->item_size == dest->item_size,
		"Cant copy array list to item that is not the same size.", false);

	if (source->length == 0)
	{
		LOG_WARNING("Copying a empty ArrayList ...");
		array_list_clear(dest);
		return true;
	}

	CHECK_COND_RET_WARN(source->length > 0,
		"Tried to copy a empty ArrayList.", false);

	if (source->length > dest->capacity)
	{
		CHECK_COND_RET(dest->is_static == false,
			"Cannot copy: destination is a static ArrayList and capacity is too small.", false);

		CHECK_COND_RET_WARN(array_list_reserve(dest, source->length - dest->capacity), 
			"Failed to reserve ArrayList.", false);
	}

	dest->length = source->length;

	memcpy(dest->data, source->data, source->length * source->item_size);

	return true;
}

void array_list_free(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot free a NULL ArrayList.", );
	CHECK_COND_RET(list->is_static == false, "Cannot free a static ArrayList.", );

	FREE_PTR_NOT_NULL(list->data, free);

	free(list);
}

bool array_list_is_empty(ArrayList* list)
{
	CHECK_IS_NULL_RET(list,
		"Cannot check if a NULL ArrayList is empty", true);

	return (list->length == 0);
}

bool array_list_resize(ArrayList* list, size_t new_capacity)
{
	CHECK_IS_NULL_RET(list, "Cannot resize a NULL ArrayList.", false);
	CHECK_COND_RET(list->is_static == false, "Cannot resize a static ArrayList.", false);

	CHECK_COND_RET(list->length <= new_capacity,
		"Cannot resize less than actual ArrayList count.", false);

	size_t new_data_size = list->item_size * new_capacity;

	unsigned char* new_data = NULL;

	// realloc se comporte comme un malloc si list->data NULL.
	new_data = realloc(list->data, new_data_size);

	if (new_data == NULL)
	{
		LOG_ERROR("Failed to alloc %zu bytes to ArrayList.", new_data_size);
		return false;
	}

	list->data = new_data;
	list->capacity = new_capacity;

	return true;
}

bool array_list_reserve(ArrayList* list, size_t size)
{
	CHECK_IS_NULL_RET(list, "Cannot reserve a NULL ArrayList.", false);
	CHECK_COND_RET(list->is_static == false, "Cannot reserve a static ArrayList.", false);

	CHECK_COND_RET_WARN(size > 0,
		"ArrayList list reseve(0) have no impact.", true);

	size_t capacity_needed = list->length + size;

	// If there is no need to reserve more, dont reserve
	if (capacity_needed <= list->capacity)
	{
		return true;
	}

	// We want to keep a *2 ratio when increasing the capacity
	size_t optimized_capacity = (list->capacity == 0) ?
		ARRAY_LIST_DEFAULT_CAPACITY : list->capacity;

	while(optimized_capacity < capacity_needed)
	{
		optimized_capacity *= 2;
	}

	return array_list_resize(list, optimized_capacity);
}

static void* array_list_get_unsafe(const ArrayList* list, size_t index)
{
	// D'après la norm C, unsigned char fait toujours 1 octet.
	return ((unsigned char*) list->data) + (index * list->item_size);
}

void* array_list_get(ArrayList* list, size_t index)
{
	CHECK_IS_NULL_RET(list, "Cannot get from a NULL ArrayList.", NULL);
	CHECK_COND_RET(index < list->length, "Invalid Array List Index.", NULL);

	return array_list_get_unsafe(list, index);
}

bool array_list_pop(ArrayList* list, void* out)
{
	CHECK_IS_NULL_RET(list, "Cannot pop from a NULL ArrayList.", false);

	// Nothing to get from an empty array_list
	if (list->length == 0)
	{
		return false;
	}

	--list->length;

	// If we dont want to get the data, we just return true
	if(out == NULL)
	{
		return true;
	}
	
	void* src = array_list_get_unsafe(list, list->length);

	memcpy(out, src, list->item_size);

	return true;
}

bool array_list_push(ArrayList* list, const void* item)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(item, "Cannot push a NULL item to ArrayList.", false);

	CHECK_COND_RET(array_list_push_new(list),
		"Failed to add a new element to ArrayList", false);

	unsigned char* dest = array_list_get_unsafe(list, list->length - 1);

	memcpy(dest, item, list->item_size);

	return true;
}

bool array_list_push_new(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot push new to a NULL ArrayList.", false);

	if (list->length >= list->capacity)
	{
		CHECK_COND_WARN(list->length > list->capacity,
			"ArrayList count was more than his capacity.");

		CHECK_COND_RET(list->is_static == false,
			"Cannot push more data to a static ArrayList.", false);

		// We need to reserve only 1 more item
		CHECK_COND_RET(array_list_reserve(list, 1),
			"Failed to reserve ArrayList cannot push", false);
	}

	++list->length;

	return true;
}

bool array_list_push_buffer(ArrayList* list, const void* items, size_t items_len)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(items, "Cannot push a NULL items ptr to ArrayList.", false);

	CHECK_COND_RET(array_list_reserve(list, items_len),
		"Failed to reserve ArrayList cannot push buffer", false);

	unsigned char* dest = array_list_get_unsafe(list, list->length);

	memcpy(dest, items, list->item_size * items_len);

	list->length += items_len;

	return true;
}

bool array_list_push_array(ArrayList* list, const ArrayList* list_to_add)
{
	CHECK_IS_NULL_RET(list, "Cannot push to a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(list_to_add, "Cannot push a NULL ArrayList to ArrayList.", false);

	CHECK_COND_RET(list != list_to_add,
		"Cannot push ArrayList to himself.", false);

	CHECK_COND_RET(list->data != list_to_add->data,
		"Cannot both ArrayList have the same buffer ??", false);

	CHECK_COND_RET(list->item_size == list_to_add->item_size,
		"Cannot push ArrayList with different item_size.", false);

	CHECK_COND_RET_WARN(list_to_add->length > 0,
		"Trying to add to ArrayList an ArrayList of count = 0.", true);

	CHECK_COND_RET_WARN(list_to_add->data != NULL,
		"ArrayList that is adding have a NULL data but count > 0 ???", true);

	return array_list_push_buffer(list, list_to_add->data, list_to_add->length);
}

void array_list_clear(ArrayList* list)
{
	CHECK_IS_NULL_RET(list, "Cannot clear a NULL ArrayList.", );

	list->length = 0;
}

bool array_list_get_int(const ArrayList* list, size_t index, int* out)
{
	CHECK_IS_NULL_RET(list, "Cannot get from a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(out, "Cannot get from ArrayList to a null ptr.", false);
	CHECK_COND_RET(index < list->length, "Invalid Array List Index.", false);

	int* in = (int*) array_list_get_unsafe(list, index);

	*out = *in;

	return true;
}

bool array_list_get_uint(const ArrayList* list, size_t index, uint* out)
{
	CHECK_IS_NULL_RET(list, "Cannot get from a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(out, "Cannot get from ArrayList to a null ptr.", false);
	CHECK_COND_RET(index < list->length, "Invalid Array List Index.", false);

	uint* in = (uint*) array_list_get_unsafe(list, index);

	*out = *in;

	return true;
}

bool array_list_pop_int(ArrayList* list, int* out)
{
	CHECK_IS_NULL_RET(list, "Cannot pop from a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(out, "Cannot pop from ArrayList to a null ptr.", false);

	CHECK_COND_RET(list->item_size == sizeof(int),
		"Tried to get a int from a ArrayList that dont have a items of this size", false);

	// Cannot pop from an empty array_list
	if (list->length == 0)
	{
		return false;
	}

	int* in = (int*) array_list_get_unsafe(list, --list->length);

	*out = *in;

	return true;
}

bool array_list_pop_uint(ArrayList* list, uint* out)
{
	CHECK_IS_NULL_RET(list, "Cannot pop from a NULL ArrayList.", false);
	CHECK_IS_NULL_RET(out, "Cannot pop from ArrayList to a null ptr.", false);

	CHECK_COND_RET(list->item_size == sizeof(uint),
		"Tried to get a unsigned int from a ArrayList that dont have a items of this size", false);

	// Cannot pop from an empty array_list
	if (list->length == 0)
	{
		return false;
	}

	uint* in = (uint*) array_list_get_unsafe(list, --list->length);

	*out = *in;

	return true;
}

