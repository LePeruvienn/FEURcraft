#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "array_list.h"

#include <stddef.h>
#include <stdbool.h>

typedef size_t (*HashMapHashFunction)    (const void* key);
typedef bool   (*HashMapCompareFunction) (const void* key1, const void* key2);

typedef struct HashMap HashMap;

struct HashMap
{
	ArrayList* buckets;

	size_t key_size;
	size_t item_size;

	size_t length;

	HashMapHashFunction    hash;
	HashMapCompareFunction compare;
};

HashMap* hash_map_create(size_t key_size, size_t item_size,
                         HashMapHashFunction hash, HashMapCompareFunction compare);

void hash_map_free(HashMap* hash_map);

void* hash_map_get(HashMap* hash_map, void* key);

void hash_map_set(HashMap* hash_map, void* key, void* item);

void hash_map_del(HashMap* hash_map, void* key);

#endif // HASH_MAP_H
