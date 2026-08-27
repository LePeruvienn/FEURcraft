#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "array_list.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct HashMap HashMap;

typedef struct HashMapEntry HashMapEntry;

struct HashMapEntry
{
	size_t key;
	bool is_empty;
	unsigned char data[]; // flexible array membres 'type[]' dont take any space in C !  
};                        // so struct global size is variable : sizeof(HashMap) + item_size

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

#endif // HASH_MAP_H
