#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stddef.h>

typedef struct ArrayList ArrayList;

struct ArrayList
{
	void* data;

	size_t item_size;

	size_t count;
	size_t capacity;
};

ArrayList* array_list_create(size_t item_size, size_t capacity);

void array_list_free(ArrayList* list);

void array_list_resize(ArrayList* list, size_t capacity);

void array_list_reserve(ArrayList* list, size_t capacity);

void* array_list_get(ArrayList* list, size_t index);

void array_list_push(ArrayList* list, void* item);

void array_list_clear(ArrayList* list);

#endif // ARRAY_LIST_H
