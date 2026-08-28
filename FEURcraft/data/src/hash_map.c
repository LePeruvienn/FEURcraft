#include "hash_map.h"
#include "hash_map_entry.h"
#include "array_list.h"
#include "linked_list.h"
#include "linked_list_iterator.h"

#include "logger.h"
#include "error_checker.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define HASH_MAP_MAX_INDEX 193

HashMap* hash_map_create(size_t key_size, size_t item_size,
                         HashMapHashFunction hash, HashMapCompareFunction compare)
{
	HashMap* hash_map = malloc(sizeof(struct HashMap));

	CHECK_IS_NULL_RET(hash_map, "Failed to allocate hashmap.", NULL);

	hash_map->buckets = array_list_create(sizeof(LinkedList*), 64);

	if (hash_map->buckets == NULL)
	{
		LOG_ERROR("Failed to create ArrayList entries of hashmap");
		free(hash_map);
		return NULL;
	}

	hash_map->key_size = key_size;
	hash_map->item_size = item_size;

	hash_map->length = 0;

	hash_map->hash = hash;
	hash_map->compare = compare;

	return hash_map;
}

void hash_map_free(HashMap* hash_map)
{
	CHECK_IS_NULL_RET(hash_map, "Cannot free a NULL HashMap", );

	ArrayList* buckets = hash_map->buckets;

	if (buckets != NULL)
	{
		for (size_t i = 0; i < buckets->length; ++i)
		{
			LinkedList** entries_ptr = array_list_get(buckets, i);

			if (entries_ptr == NULL)
				continue;
			
			LinkedList* entries = *entries_ptr;

			if (entries == NULL)
				continue;

			linked_list_free(entries);
		}

		array_list_free(buckets);
	}

	free(hash_map);
}

static size_t hash_map_hash(HashMap* map, const void* key)
{
	return map->hash(key) % HASH_MAP_MAX_INDEX;
};

static HashMapEntry hash_map_get_entry_from(HashMap* map, LinkedList* entries, const void* key)
{
	LinkedListIterator iterator;
	linked_list_iterator_init(&iterator, entries);

	do {
		HashMapEntryStorage* storage = linked_list_iterator_get_data(&iterator);

		if (storage == NULL)
			continue;

		HashMapEntry entry = hash_map_entry_storage_get_entry(storage, map->key_size);

		bool is_same_key = map->compare(entry.key, key);

		if (is_same_key == false)
			continue;

		return entry;

	} while(linked_list_iterator_go_next(&iterator));

	return HASH_MAP_ENTRY_EMPTY;
}

void* hash_map_get(HashMap* map, const void* key)
{
	CHECK_IS_NULL_RET(map, "Cannot get from a NULL HashMap", NULL);

	size_t i = hash_map_hash(map, key);

	if (i >= map->buckets->length)
	{
		return NULL;
	}

	LinkedList** entries_ptr = array_list_get(map->buckets, i);

	CHECK_IS_NULL_RET(entries_ptr, "ArrayList get is NULL bad index.", NULL);

	LinkedList* entries = *entries_ptr;

	if (entries == NULL)
	{
		return NULL;
	}

	HashMapEntry entry = hash_map_get_entry_from(map, entries, key);

	if (hash_map_entry_is_empty(entry) == false)
	{
		return (entry.storage->is_empty) ? NULL : entry.value;
	}
	
	return NULL;
}

void hash_map_set(HashMap* map, const void* key, const void* value)
{
	CHECK_IS_NULL_RET(map, "Cannot set to a NULL HashMap", );

	size_t i = hash_map_hash(map, key);

	if (i >= map->buckets->length)
	{
		size_t old_length = map->buckets->length;

		array_list_resize(map->buckets, i + 1);

		// by default all the values are set to 0 but in case ....
		void* empty_ptr = NULL;
		array_list_fill_at(map->buckets, &empty_ptr, old_length, map->buckets->length - 1);
	}

	CHECK_COND_RET(map->buckets->length > i,
		"HashMap bucket is too small for current index", );

	LinkedList** entries_ptr = array_list_get(map->buckets, i);

	CHECK_IS_NULL_RET(entries_ptr, "ArrayList get is NULL bad index.", );

	if (*entries_ptr == NULL)
	{
		size_t storage_size = sizeof(struct HashMapEntryStorage) + map->key_size + map->item_size;
		*entries_ptr = linked_list_create(storage_size);
	}

	LinkedList* entries = *entries_ptr;

	HashMapEntry entry = hash_map_get_entry_from(map, entries, key);

	if (entry.storage == NULL)
	{
		entry.storage = linked_list_push_back(entries);
	}

	hash_map_entry_storage_set(entry.storage, key, value, map->key_size, map->item_size);
}


// NOTE: Ici je free pas les noeuds mort pour les réutiliser mais peut être que c'est guez ?
//       jsp en vrai perso je kiff 😎🤙
void hash_map_del(HashMap* map, const void* key)
{
	CHECK_IS_NULL_RET(map, "Cannot del a value of a NULL HashMap", );

	size_t i = hash_map_hash(map, key);

	if (i >= map->buckets->length)
		return;

	LinkedList** entries_ptr = array_list_get(map->buckets, i);

	CHECK_IS_NULL_RET(entries_ptr, "ArrayList get is NULL bad index.", );

	LinkedList* entries = *entries_ptr;

	if (entries == NULL)
		return;

	HashMapEntry entry = hash_map_get_entry_from(map, entries, key);

	if (hash_map_entry_is_empty(entry))
		return;

	if(entry.storage->is_empty == true)
		return;
	
	entry.storage->is_empty = true;
}

