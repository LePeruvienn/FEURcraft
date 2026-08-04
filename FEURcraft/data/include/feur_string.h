#ifndef FEUR_STRING_H
#define FEUR_STRING_H

#include <stddef.h>
#include <stdbool.h>

#define FEUR_STR_BEGIN 0
#define FEUR_C_STR_EMPTY "\0"

#define FEUR_STR_STATIC(_buffer, _capacity, _init_str) \
	((FeurString) { .c_str = strcpy((_buffer), (_init_str)), \
	                .length = strlen(_init_str), \
	                .capacity = (_capacity), \
	                .is_static = true })

#define FEUR_STR_STATIC_INIT(_buffer, _capacity, _length) \
	((FeurString) { .c_str = (_buffer), \
	                .capacity = (_capacity), \
	                .length = _length, \
	                .is_static = true })

	

typedef struct FeurString FeurString;

struct FeurString
{
	char* c_str;
	size_t length;
	size_t capacity;

	bool is_static;
};

FeurString* feur_string_create(size_t capacity);
FeurString* feur_string_create_c_str(const char* c_str);
FeurString* feur_string_create_c_str_size(const char* c_str, size_t size);

FeurString* feur_string_create_from(FeurString* string, size_t beg, size_t end);

FeurString* feur_string_create_copy(FeurString* string);

void feur_string_free(FeurString* string);

void feur_string_resize(FeurString* string, size_t new_capacity);
void feur_string_reserve(FeurString* string, size_t capacity);

void feur_string_set_c_str(FeurString* string, const char* c_str, size_t beg);
void feur_string_set_c_str_size(FeurString* string, const char* c_str, size_t size, size_t beg);

void feur_string_append(FeurString* dest, const FeurString* string);
void feur_string_append_str(FeurString* dest, const char* c_str);

bool feur_string_equal(const FeurString* s1, const FeurString* s2);

#endif // FEUR_STRING_H
