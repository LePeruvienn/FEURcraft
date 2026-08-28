#ifndef HASH_MAP_ENTRY_H
#define HASH_MAP_ENTRY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define HASH_MAP_ENTRY_EMPTY ((HashMapEntry) { .key = NULL, .value = NULL, .storage = NULL })

typedef struct HashMapEntryStorage HashMapEntryStorage;

struct HashMapEntryStorage
{
	// to save is buffer is saving data or not
	bool is_empty;

	// flexible array membres 'type[]' dont take any space in C !
	// contains key + value data
	unsigned char data[];
};

typedef struct HashMapEntry HashMapEntry;

struct HashMapEntry
{
	void* key;
	void* value;

	HashMapEntryStorage* storage;
};

HashMapEntry hash_map_entry_storage_get_entry(HashMapEntryStorage* storage, size_t key_size);

void hash_map_entry_storage_set(HashMapEntryStorage* storage,
                                const void* key, const void* value,
                                size_t key_size, size_t value_size);

bool hash_map_entry_is_empty(HashMapEntry entry);

#endif // HASH_MAP_ENTRY_H
