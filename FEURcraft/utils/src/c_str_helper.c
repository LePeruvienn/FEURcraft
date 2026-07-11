#include "c_str_helper.h"

#include "logger.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

void c_str_to_upper(char* str)
{
	if (str == NULL)
	{
		LOG_WARNING("Tried to upper a NULL char* .");
		return;
	}

	for(size_t i = 0; str[i] != '\0'; ++i)
	{
		str[i] = toupper(str[i]);
	}
}

void c_str_to_lower(char* str)
{
	if (str == NULL)
	{
		LOG_WARNING("Tried to lower a NULL char* .");
		return;
	}

	for(size_t i = 0; str[i] != '\0'; ++i)
	{
		str[i] = tolower(str[i]);
	}
}

void c_str_trim(char* str)
{
	char *start = str + strspn(str, " \t\n\r");  // Points to the first non-whitespace character
	char *end = str + strlen(str) - 1;  // Points to the last character of the string

	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
	{
		--end;  // Move the end pointer backward while it points to whitespace
	}

	*(end + 1) = '\0';  // Place the null terminator after the last non-whitespace character

	// Move the trimmed string to the start of the buffer
	if (start > str)
	{
		memmove(str, start, end - start + 2);  // +2 to include the last character and null terminator
	}
}

bool c_str_is_empty(const char* str)
{
	if (str == NULL)
	{
		return true;
	}

	if (str[0] == '\0')
	{
		return true;
	}

	for(size_t i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r')
		{
			return false;
		}
	}

	return true;
}

bool c_str_mean_false(const char* str)
{
	if (c_str_is_empty(str))
	{
		return false;
	}

	const size_t buf_size = 32;
	char tmp[buf_size];
	strncpy(tmp, str, buf_size);

	c_str_trim(tmp);
	c_str_to_lower(tmp);

	if (tmp[0] == '0' || strcmp(tmp, "false") == 0 || strcmp(tmp, "no"))
	{
		return true;
	}

	return false;
}

bool c_str_mean_true(const char* str)
{
	if (c_str_is_empty(str))
	{
		return false;
	}

	const size_t buf_size = 32;
	char tmp[buf_size];
	strncpy(tmp, str, buf_size);

	c_str_trim(tmp);
	c_str_to_lower(tmp);

	if (tmp[0] == '0' || strcmp(tmp, "true") == 0 || strcmp(tmp, "yes"))
	{
		return true;
	}

	return false;
}
