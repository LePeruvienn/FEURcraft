#include "string_hash_map.h"

#include "logger.h"
#include "error_checker.h"
#include "ptr_helper.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// https://cp-algorithms.com/string/string-hashing.html
static size_t string_hash_map_hash(const void* str_ptr)
{
	const char* string = str_ptr;

	const int p = 31;
	const int m = 1e9 + 9;
	size_t hash_value = 0;
	size_t p_pow = 1;

	size_t len = strlen(string);

	for (size_t i = 0; i < len; ++i)
	{
		char c = string[i];
		hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;
	}

	return hash_value;
}

static bool string_hash_map_compare(const void* str_ptr_1, const void* str_ptr_2)
{
	const char* str_1 = str_ptr_1;
	const char* str_2 = str_ptr_2;

	return strcmp(str_1, str_2) == 0;
}

StringHashMap* string_hash_map_create(size_t max_string_size, size_t item_size)
{
	StringHashMap* str_map = malloc(sizeof(struct StringHashMap));

	CHECK_IS_NULL_RET(str_map, "Failed to malloc StringHashMap", NULL);

	str_map->map = hash_map_create(max_string_size + 1, item_size, 
	                               string_hash_map_hash, string_hash_map_compare);

	if (str_map->map == NULL)
	{
		LOG_ERROR("Failed to create HashMap implemenation of String HashMap");
		free(str_map);
		return NULL;
	}

	str_map->max_string_size = max_string_size;

	return str_map;
}

void string_hash_map_free(StringHashMap* str_map)
{
	CHECK_IS_NULL_RET(str_map, "Cannot free a NULL StringHashMap", );

	FREE_PTR_NOT_NULL(str_map->map, hash_map_free);
	free(str_map);
}

bool string_hash_map_get(StringHashMap* str_map, const char* key, void* out)
{
	CHECK_IS_NULL_RET(str_map, "Cannot get from a NULL StringHashMap.", NULL);
	CHECK_IS_NULL_RET(key, "Cannot get from a StringHashMap with a NULL key", NULL);

	CHECK_COND_RET(strlen(key) <= str_map->max_string_size,
		"Cannot get Key of StringHashMap that have a length greater than max size.", NULL);

	return hash_map_get(str_map->map, key, out);
}

void* string_hash_map_get_modify(StringHashMap* str_map, const char* key)
{
	CHECK_IS_NULL_RET(str_map, "Cannot get from a NULL StringHashMap.", NULL);
	CHECK_IS_NULL_RET(key, "Cannot get from a StringHashMap with a NULL key", NULL);

	CHECK_COND_RET(strlen(key) <= str_map->max_string_size,
		"Cannot get Key of StringHashMap that have a length greater than max size.", NULL);

	return hash_map_get_modify(str_map->map, key);
}

bool string_hash_map_exists(StringHashMap* str_map, const char* key)
{
	CHECK_IS_NULL_RET(str_map, "Cannot check exists from a NULL StringHashMap.", NULL);
	CHECK_IS_NULL_RET(key, "Cannot check exists from a StringHashMap with a NULL key", NULL);

	CHECK_COND_RET(strlen(key) <= str_map->max_string_size,
		"Cannot check exists Key of StringHashMap that have a length greater than max size.", NULL);

	return hash_map_exists(str_map->map, key);
}

void string_hash_map_set(StringHashMap* str_map, const char* key, const void* value)
{
	CHECK_IS_NULL_RET(str_map, "Cannot set to a NULL StringHashMap.", );
	CHECK_IS_NULL_RET(key, "Cannot set to a StringHashMap with a NULL key", );
	CHECK_IS_NULL_RET(value, "Cannot set a NULl value to a StringHashMap", );

	CHECK_COND_RET(strlen(key) <= str_map->max_string_size,
		"Cannot set Key of StringHashMap that have a length size greater than max size.", );

	hash_map_set(str_map->map, key, value);
}

void string_hash_map_del(StringHashMap* str_map, const char* key)
{
	CHECK_IS_NULL_RET(str_map, "Cannot del to a NULL StringHashMap.", );
	CHECK_IS_NULL_RET(key, "Cannot del to a StringHashMap with a NULL key", );

	CHECK_COND_RET(strlen(key) <= str_map->max_string_size,
		"Cannot del Key of StringHashMap that have a length size greater than max size.", );

	hash_map_del(str_map->map, key);
}
