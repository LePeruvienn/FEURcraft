#include "hash_map.h"
#include "array_list.h"
#include "linked_list.h"
#include "linked_list_iterator.h"

#include "ptr_helper.h"

#include "logger.h"
#include "error_checker.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define PRIME_NUMBER 193

typedef struct HashMapEntry HashMapEntry;

struct HashMapEntry
{
	size_t key;
	bool is_empty;
	unsigned char data[]; // flexible array membres 'type[]' dont take any space in C !  
};                        // so struct global size is variable : sizeof(HashMap) + item_size

HashMap* hash_map_create(size_t item_size)
{
	HashMap* hash_map = malloc(sizeof(struct HashMap));

	CHECK_IS_NULL_RET(hash_map, "Failed to allocate hashmap.", NULL);

	hash_map->item_size = item_size;

	hash_map->buckets = array_list_create(sizeof(LinkedList*), PRIME_NUMBER);

	if (hash_map->buckets == NULL)
	{
		LOG_ERROR("Failed to create ArrayList entries of hashmap");
		free(hash_map);
		return NULL;
	}

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

static size_t hash_map_hash(size_t key)
{
	return key * (key + 3) % PRIME_NUMBER;
};

static HashMapEntry* hash_map_find_entry(LinkedList* entries, size_t key)
{
	LinkedListIterator iterator;
	linked_list_iterator_init(&iterator, entries);

	do {
		HashMapEntry* entry = linked_list_iterator_get_data(&iterator);

		if (entry == NULL)
			continue;

		if (entry->key != key)
			continue;

		return entry;

	} while(linked_list_iterator_go_next(&iterator));

	return NULL;
}

void* hash_map_get(HashMap* hash_map, size_t key)
{
	CHECK_IS_NULL_RET(hash_map, "Cannot get from a NULL HashMap", NULL);

	size_t i = hash_map_hash(key);

	if (i >= hash_map->buckets->length)
	{
		return NULL;
	}

	LinkedList** entries_ptr = array_list_get(hash_map->buckets, i);

	CHECK_IS_NULL_RET(entries_ptr, "ArrayList get is NULL bad index.", NULL);

	LinkedList* entries = *entries_ptr;

	if (entries == NULL)
	{
		return NULL;
	}

	HashMapEntry* entry = hash_map_find_entry(entries, key);

	if (entry != NULL)
	{
		return (entry->is_empty) ? NULL : entry->data;
	}
	
	return NULL;
}

void hash_map_set(HashMap* hash_map, size_t key, void* item)
{
	CHECK_IS_NULL_RET(hash_map, "Cannot set to a NULL HashMap", );

	size_t i = hash_map_hash(key);

	if (i >= hash_map->buckets->length)
	{
		size_t old_length = hash_map->buckets->length;

		array_list_resize(hash_map->buckets, i + 1);

		// by default all the values are set to 0 but in case ....
		void* empty_ptr = NULL;
		array_list_fill_at(hash_map->buckets, &empty_ptr, old_length, hash_map->buckets->length - 1);
	}

	CHECK_COND_RET(hash_map->buckets->length > i,
		"HashMap bucket is too small for current index", );

	LinkedList** entries_ptr = array_list_get(hash_map->buckets, i);

	CHECK_IS_NULL_RET(entries_ptr, "ArrayList get is NULL bad index.", );

	if (*entries_ptr == NULL)
	{
		*entries_ptr = linked_list_create(sizeof(struct HashMapEntry) + hash_map->item_size);
	}

	LinkedList* entries = *entries_ptr;

	HashMapEntry* entry = hash_map_find_entry(entries, key);

	if (entry == NULL)
	{
		entry = linked_list_push_back(entries);

		CHECK_IS_NULL_RET(entry, "Failed to add a new enry to HashMap", );

		entry->key = key;
		entry->is_empty = true;
	}

	memcpy(entry->data, item, hash_map->item_size);
	entry->is_empty = false;
}

void hash_map_del(HashMap* hash_map, size_t key)
{
	CHECK_IS_NULL_RET(hash_map, "Cannot del a value of a NULL HashMap", );

	size_t i = hash_map_hash(key);

	if (i >= hash_map->buckets->length)
		return;

	LinkedList** entries_ptr = array_list_get(hash_map->buckets, i);

	CHECK_IS_NULL_RET(entries_ptr, "ArrayList get is NULL bad index.", );

	LinkedList* entries = *entries_ptr;

	if (entries == NULL)
		return;

	HashMapEntry* entry = hash_map_find_entry(entries, key);

	if (entry == NULL)
		return;

	if(entry->is_empty == true)
		return;
	
	entry->is_empty = true;
}

