#include "env_helper.h"
#include "c_str_helper.h"

#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

int env_get_int(char *name, int *out)
{
	char *value = getenv(name);

	if (value == NULL || *value == '\0')
	{
		return 1;
	}

	char *end;
	errno = 0;

	long n = strtol(value, &end, 10);

	if (end == value || *end != '\0')
	{
		return 2;
	}

	if (errno == ERANGE)
	{
		return 3;
	}

	*out = (int) n;

	return 0;
}

int env_get_float(char *name, float *out)
{
	char *value = getenv(name);

	if (value == NULL || *value == '\0')
	{
		return 1;
	}

	char *end;
	errno = 0;

	float f = strtof(value, &end);

	if (end == value || *end != '\0')
	{
		return 2;
	}

	if (errno == ERANGE)
	{
		return 3;
	}

	*out = f;

	return 0;
}

bool env_get_bool(char *name)
{
	const char *value = getenv(name);

	return c_str_mean_true(value);
}
