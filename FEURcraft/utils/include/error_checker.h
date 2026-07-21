#ifndef UTILS_ERROR_CHECKER_H
#define UTILS_ERROR_CHECKER_H

#include "logger.h"

#include <stdlib.h>

#define CHECK_RET_VOID

#define CHECK_COND(cond, error_msg) \
	if (cond) {} \
	else  \
	{ \
		LOG_ERROR(error_msg); \
	}

#define CHECK_COND_RET(cond, error_msg, ret) \
	if (cond) {} \
	else  \
	{ \
		LOG_ERROR(error_msg); \
		return ret; \
	}

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

#endif // UTILS_ERROR_CHECKER_H
