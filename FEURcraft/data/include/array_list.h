#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stddef.h>
#include <stdbool.h>

#define ARRAY_LIST_STATIC(_data, _item_size, _count, _capacity) \
	((ArrayList) { .data = (_data), \
	               .item_size = (_item_size), \
	               .count = (_count), \
	               .capacity = (_capacity), \
	               .is_static = true })

typedef struct ArrayList ArrayList;

struct ArrayList
{
	void* data;

	size_t item_size;

	size_t count;
	size_t capacity;

	bool is_static; // DONT MANIP THIS
};

ArrayList* array_list_create(size_t item_size, size_t capacity);

void array_list_free(ArrayList* list);

void array_list_resize(ArrayList* list, size_t capacity);

void array_list_reserve(ArrayList* list, size_t capacity);

void* array_list_get(const ArrayList* list, size_t index);

void array_list_push(ArrayList* list, const void* item);

void array_list_push_buffer(ArrayList* list, const void* items, size_t items_len);

void array_list_push_array(ArrayList* list, const ArrayList* list_to_add);

void array_list_clear(ArrayList* list);

#endif // ARRAY_LIST_H
