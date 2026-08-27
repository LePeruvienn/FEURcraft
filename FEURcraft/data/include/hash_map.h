#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "array_list.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct HashMap HashMap;

struct HashMap
{
	ArrayList* buckets;

	size_t item_size;
	size_t length;
};

HashMap* hash_map_create(size_t item_size);

void hash_map_free(HashMap* hash_map);

void* hash_map_get(HashMap* hash_map, size_t key);

void hash_map_set(HashMap* hash_map, size_t key, void* item);

void hash_map_del(HashMap* hash_map, size_t key);

#endif // HASH_MAP_H
