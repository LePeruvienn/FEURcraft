#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "array_list.h"

#include <stddef.h>

typedef struct HashMap HashMap;

typedef struct HashMapEntry HashMapEntry;

struct HashMapEntry
{
	size_t i;
	void* data;
};

struct HashMap
{
	ArrayList* map;

	size_t item_size;
};

HashMap* hash_map_create(size_t item_size);

void hash_map_free(HashMap* hash_map);

void* hash_map_get(HashMap* hash_map, size_t i);

void hash_map_set(HashMap* hash_map, size_t i, void* item);

#endif // HASH_MAP_H
