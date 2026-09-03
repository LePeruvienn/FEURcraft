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

void hash_map_free(HashMap* map);

void* hash_map_get(HashMap* map, const void* key);

bool hash_map_exists(HashMap* map, const void* key);

void hash_map_set(HashMap* map, const void* key, const void* item);

void hash_map_del(HashMap* map, const void* key);

#endif // HASH_MAP_H
