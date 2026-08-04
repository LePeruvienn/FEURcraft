#include "feur_string.h"

#include "error_checker.h"
#include "logger.h"
#include "ptr_helper.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define FEUR_STRING_MIN_CAPACITY 8

FeurString* feur_string_create(size_t capacity)
{
	FeurString* string = malloc(sizeof(struct FeurString));

	CHECK_IS_NULL_RET(string, "Failed to malloc FeurString struct.", NULL);

	size_t optimized_capacity = FEUR_STRING_MIN_CAPACITY;

	while(optimized_capacity < capacity)
	{
		optimized_capacity *= 2;
	}

	string->capacity = optimized_capacity;
	string->c_str = malloc(sizeof(char) * string->capacity);

	if (string->c_str == NULL)
	{
		LOG_ERROR("Failed to malloc FeurString char buffer.");
		free(string);
		return NULL;
	}

	string->length = 0;
	string->c_str[0] = '\0';
	string->is_static = false;

	return string;
}

FeurString* feur_string_create_c_str(const char* c_str)
{
	CHECK_IS_NULL_RET(c_str, "Cannot create a FeurString from a NULL char*.", NULL);

	size_t size = strlen(c_str);

	return feur_string_create_c_str_size(c_str, size);
}

FeurString* feur_string_create_c_str_size(const char* c_str, size_t size)
{
	CHECK_IS_NULL_RET(c_str, "Cannot create a FeurString from a NULL char*.", NULL);
	CHECK_COND_RET(size > 0, "Cannot create a FeurString with a const char* of size 0", NULL);

	FeurString* string = feur_string_create(size + 1);

	CHECK_IS_NULL_RET(string, "Failed to create FeurString.", NULL);

	feur_string_set_c_str_size(string, c_str, size, 0);

	return string;
}

FeurString* feur_string_create_from(FeurString* string, size_t beg, size_t end)
{
	CHECK_IS_NULL_RET(string, "Cannot create a FeurString from a NULL ptr.", NULL);

	bool is_beg_end_valid = (end >= beg) && (end < string->length);

	CHECK_COND_RET(is_beg_end_valid, "Cannot create FeurString, indices are not valid or out of bounds", NULL);

	size_t size = end - beg + 1;

	const char* c_str = string->c_str + beg;

	return feur_string_create_c_str_size(c_str, size);
}

void feur_string_set_c_str(FeurString* string, const char* c_str, size_t beg)
{
	CHECK_IS_NULL_RET(c_str, "Cannot set a FeurString from a NULL char*.", );

	size_t size = strlen(c_str);

	feur_string_set_c_str_size(string, c_str, size, beg);
}

void feur_string_free(FeurString* string)
{
	CHECK_IS_NULL_RET(string, "Cannot free a NULL FeurString", );
	CHECK_COND_RET(string->is_static == false, "Cannot free a static FeurString.", );

	FREE_PTR_NOT_NULL(string->c_str, free);
	free(string);
}

void feur_string_resize(FeurString* string, size_t new_capacity)
{
	CHECK_IS_NULL_RET(string, "Cannot resize a NULL FeurString.", );
	CHECK_COND_RET(string->is_static == false, "Cannot resize a static FeurString.", );

	CHECK_COND_RET(string->length + 1 <= new_capacity,
		"Cannot resize less than actual FeurString length + 1.", );

	char* new_c_str = realloc(string->c_str, new_capacity);

	if (new_c_str == NULL)
	{
		LOG_ERROR("Failed to alloc %zu bytes to FeurString.", new_capacity);
		return;
	}

	string->c_str = new_c_str;
	string->capacity = new_capacity;
}

void feur_string_reserve(FeurString* string, size_t capacity)
{
	CHECK_IS_NULL_RET(string, "Cannot reserve a NULL FeurString.", );
	CHECK_COND_RET(string->is_static == false, "Cannot reserve a static FeurString.", );

	CHECK_COND_RET_WARN(capacity > 0,
		"FeurString reserve(0) have no impact.", );

	feur_string_resize(string, string->capacity + capacity);
}

void feur_string_set_c_str_size(FeurString* string, const char* c_str, size_t size, size_t beg)
{
	CHECK_IS_NULL_RET(string, "Cannot set a FeurString that is NULL ptr.",);
	CHECK_IS_NULL_RET(c_str, "Cannot set a FeurString from a NULL char*.", );
	CHECK_COND_RET(size > 0, "Cannot set a FeurString with a char* of size 0", );
	
	CHECK_COND_RET(beg <= string->length, "Cannot set a FeurString with beg > length", );

	size_t new_length_needed = beg + size;

	if (new_length_needed + 1 > string->capacity)
	{
		CHECK_COND_RET(string->is_static == false,
			"Cannot expand a static FeurString.", );

		size_t capacity_needed = (string->capacity == 0) ?
			FEUR_STRING_MIN_CAPACITY : string->capacity;

		while (new_length_needed + 1 > capacity_needed)
		{
			capacity_needed *= 2;
		}

		feur_string_resize(string, capacity_needed);
	}

	memcpy(string->c_str + beg, c_str, size);

	if (new_length_needed > string->length)
	{
		string->length = new_length_needed;
	}

	string->c_str[string->length] = '\0';
}

void feur_string_append(FeurString* dest, const FeurString* src)
{
	CHECK_IS_NULL_RET(dest, "Cannot append to a NULL FeurString.", );
	CHECK_IS_NULL_RET(src, "Cannot append a NULL FeurString.", );

	if (src->length == 0)
	{
		return;
	}

	feur_string_set_c_str_size(dest, src->c_str, src->length, dest->length);
}

void feur_string_append_str(FeurString* dest, const char* c_str)
{
	CHECK_IS_NULL_RET(dest, "Cannot append to a NULL FeurString.", );
	CHECK_IS_NULL_RET(c_str, "Cannot append a NULL char*.", );

	size_t size = strlen(c_str);
	
	if (size == 0)
	{
		return;
	}

	feur_string_set_c_str_size(dest, c_str, size, dest->length);
}

bool feur_string_equal(const FeurString* s1, const FeurString* s2)
{
	CHECK_IS_NULL_RET(s1, "Cannot compare a NULL FeurString", false);
	CHECK_IS_NULL_RET(s2, "Cannot compare a NULL FeurString", false);

	if (s1 == s2)
	{
		return true;
	}

	if (s1->length != s2->length)
	{
		return false;
	}

	return memcmp(s1->c_str, s2->c_str, s1->length) == 0;
}
