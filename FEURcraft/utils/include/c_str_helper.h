#ifndef C_STR_HELPER_H
#define C_STR_HELPER_H

#include <stdbool.h>

void c_str_to_upper(char* str);
void c_str_to_lower(char* str);

void c_str_trim(char* str);

bool c_str_is_empty(const char* str);

bool c_str_mean_false(const char* str);
bool c_str_mean_true(const char* str);

#endif // C_STR_HELPER_H
