#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

/**
 * \file array_list.h
 * \brief Liste dynamique
 *
 * \ref ArrayList est une structure permmettant de manipuler des listes d'élément 
 * peut importe leurs type. Elle peut être alloué sur le tas ou sur la pile via un buffer 
 * en variable local via la macro \ref ARRAY_LIST_STATIC
 */

#include "feur_types.h"

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

	size_t length;
	size_t capacity;

	bool is_static; // DONT MANIP THIS
};

ArrayList* array_list_create(size_t item_size, size_t capacity);

bool array_list_copy(const ArrayList* source, ArrayList* dest);

void array_list_free(ArrayList* list);

bool array_list_is_empty(ArrayList* list);

bool array_list_resize(ArrayList* list, size_t capacity);

bool array_list_reserve(ArrayList* list, size_t size);

void* array_list_get(ArrayList* list, size_t index);

bool array_list_pop(ArrayList* list, void* out);

bool array_list_push(ArrayList* list, const void* item);

bool array_list_push_new(ArrayList* list);

bool array_list_push_buffer(ArrayList* list, const void* items, size_t items_len);

bool array_list_push_array(ArrayList* list, const ArrayList* list_to_add);

void array_list_clear(ArrayList* list);


bool array_list_get_int(const ArrayList* list, size_t index, int* out);
bool array_list_get_uint(const ArrayList* list, size_t index, uint* out);

bool array_list_pop_int(ArrayList* list, int* out);
bool array_list_pop_uint(ArrayList* list, uint* out);

#endif // ARRAY_LIST_H
