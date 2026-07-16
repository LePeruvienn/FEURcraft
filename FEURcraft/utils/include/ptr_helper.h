#ifndef UTILS_PTR_HELPER_H
#define UTILS_PTR_HELPER_H

#include "logger.h"

#include <stdlib.h>

#define RET_VOID

#define CHECK_IS_NULL(ptr, error_msg) \
	if (ptr == NULL) \
	{ \
		LOG_ERROR(error_msg); \
	}

#define CHECK_IS_NULL_RET(ptr, error_msg, ret) \
	if (ptr == NULL) \
	{ \
		LOG_ERROR(error_msg); \
		return ret; \
	}

#define FREE_PTR_NOT_NULL(ptr, free_func) \
	if (ptr != NULL) \
	{ \
		free_func(ptr); \
		ptr = NULL; \
	}

#endif // UTILS_PTR_HELPER_H
