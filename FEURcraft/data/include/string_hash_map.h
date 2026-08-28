#ifndef STRING_HASH_MAP_H
#define STRING_HASH_MAP_H

#include "hash_map.h"

typedef struct StringHashMap StringHashMap;

struct StringHashMap
{
	HashMap* map;

	size_t max_string_size;
};

StringHashMap* string_hash_map_create(size_t max_string_size, size_t item_size);

void string_hash_map_free(StringHashMap* str_map);

void* string_hash_map_get(StringHashMap* str_map, const char* key);

void string_hash_map_set(StringHashMap* str_map, const char* key, const void* value);

void string_hash_map_del(StringHashMap* str_map, const char* key);


#endif // STRING_HASH_MAP