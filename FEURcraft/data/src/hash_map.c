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

#define PRIME_NUMBER 193

HashMap* hash_map_create(size_t item_size)
{
	HashMap* hash_map = malloc(sizeof(struct HashMap));

	CHECK_IS_NULL_RET(hash_map, "Failed to allocate hashmap.", NULL);

	hash_map->item_size = item_size;

	hash_map->map = array_list_create(sizeof(LinkedList*), 64);

	if (hash_map->map == NULL)
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

	FREE_PTR_NOT_NULL(hash_map->map, array_list_free);
	free(hash_map);
}

static size_t hash_map_hash(size_t i)
{
	return i * (i + 3) % PRIME_NUMBER; 
};

// TODO: FIX
void* hash_map_get(HashMap* hash_map, size_t i)
{
	CHECK_IS_NULL_RET(hash_map, "Cannot get from a NULL HashMap", NULL);

	if (i >= hash_map->map->length)
	{
		return NULL;
	}

	size_t key = hash_map_hash(i);

	LinkedList* entries = array_list_get(hash_map->map, key);

	if (entries == NULL)
	{
		return NULL;
	}

	LinkedListIterator iterator;
	linked_list_iterator_init(&iterator, entries);

	HashMapEntry* entry = linked_list_iterator_get_data(&iterator);

	if (entry == NULL)
	{
		return NULL;
	}

	while(linked_list_iterator_go_next(&iterator))
	{
		entry = linked_list_iterator_get_data(&iterator);

		if (entry == NULL)
			continue;

		if (entry->i != i)
			continue;

		return entry->data;
	}
	
	return NULL;
}

// TODO: FIX
void hash_map_set(HashMap* hash_map, size_t i, void* item)
{
	CHECK_IS_NULL_RET(hash_map, "Cannot set to a NULL HashMap", );

	size_t key = hash_map_hash(i);

	if (key >= hash_map->map->length)
	{
		size_t old_length = hash_map->map->length;

		array_list_resize(hash_map->map, key);

		// by default all the values are set to 0 but in case ....
		void* empty_ptr = NULL;
		array_list_fill_at(hash_map->map, &empty_ptr, old_length, hash_map->map->length - 1);
	}

	LinkedList** entries_ptr = array_list_get(hash_map->map, key);

	CHECK_IS_NULL_RET(entries_ptr, "cannot be null", );

	if (*entries_ptr == NULL)
	{
		*entries_ptr = linked_list_create(hash_map->item_size);
	}

	LinkedList* entries = *entries_ptr;

	linked_list_push_back(entries, item);
}
