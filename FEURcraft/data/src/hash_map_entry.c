#include "hash_map_entry.h"

#include "error_checker.h"

#include <stddef.h>
#include <string.h>

HashMapEntry hash_map_entry_storage_get_entry(HashMapEntryStorage* storage, size_t key_size)
{
	HashMapEntry entry = HASH_MAP_ENTRY_EMPTY;

	CHECK_IS_NULL_RET(storage, "Cannot get entry from a NULL HashMapEntryStorage", entry);
	CHECK_COND_RET(key_size != 0, "KeySize cannot be equal to zero", entry);

	entry.key = storage->data;
	entry.value = storage->data + key_size;
	entry.storage = storage;

	return entry;
}

void hash_map_entry_storage_set(HashMapEntryStorage* storage,
                                const void* key, const void* value,
                                size_t key_size, size_t value_size)
{
	CHECK_IS_NULL_RET(storage, "Cannot set a NULL HashMapEntryStorage", );
	CHECK_IS_NULL_RET(storage->data, "Cannot set a HashMapEntryStorage with NULL data", );

	CHECK_IS_NULL_RET(key, "Cannot set storage from a NULL key", );
	CHECK_IS_NULL_RET(value, "Cannot set storage from a NULL value", );

	CHECK_COND_RET(key_size != 0, "KeySize cannot be equal to zero", );
	CHECK_COND_RET(value_size != 0, "KeySize cannot be equal to zero", );

	HashMapEntry entry = hash_map_entry_storage_get_entry(storage, key_size);

	CHECK_COND_RET(entry.key != NULL && entry.value != NULL,
		"Failed to get HashMapEntry from storage", );

	memcpy(entry.key, key, key_size);
	memcpy(entry.value, value, value_size);

	entry.storage->is_empty = false;
}

bool hash_map_entry_is_empty(HashMapEntry entry)
{
	return (entry.key     == NULL ||
	        entry.value   == NULL ||
	        entry.storage == NULL );
}
