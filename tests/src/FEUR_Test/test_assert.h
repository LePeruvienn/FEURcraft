#ifndef FEUR_TEST_ASSERT_H
#define FEUR_TEST_ASSERT_H

#include "test_logger.h"

#include <math.h>
#include <stdlib.h>

#define EPSILON 0.00001f

#define FEUR_TEST_LOG_ERROR_MSG(msg) \
	if (msg == NULL) \
	{ \
		FEUR_TEST_LOG_ERROR("Assertion failed"); \
	} \
	else \
	{ \
		FEUR_TEST_LOG_ERROR(msg); \
	}

/*
 * ASSERT MACRO WITHOUT MESSAGE
 */

#define FEUR_TEST_ASSERT(cond) \
	FEUR_TEST_ASSERT_MSG(cond, "Condition is false, Assertion Failed !")

#define FEUR_TEST_ASSERT_NULL(ptr) \
	FEUR_TEST_ASSERT_NULL_MSG(ptr, "Pointer is NOT NULL, Assertion Failed !")

#define FEUR_TEST_ASSERT_NOT_NULL(ptr) \
	FEUR_TEST_ASSERT_NOT_NULL_MSG(ptr, "Point is NULL, Assertion Failed !")

#define FEUR_TEST_ASSERT_FLOAT(a, b) \
	FEUR_TEST_ASSERT_FLOAT_MSG(a, b, "Float are not ~ equal, Assertion Failed !")

/*
 * ASSERT MACRO WITH MESSAGE
 */

#define FEUR_TEST_ASSERT_MSG(cond, msg) \
	if(!(cond)) \
	{ \
		FEUR_TEST_LOG_ERROR_MSG(msg); \
		return FEUR_Test_Failed; \
	} else {}


#define FEUR_TEST_ASSERT_NULL_MSG(ptr, msg) \
	if((ptr) != NULL) \
	{ \
		FEUR_TEST_LOG_ERROR_MSG(msg); \
		return FEUR_Test_Failed; \
	} else {}

#define FEUR_TEST_ASSERT_NOT_NULL_MSG(ptr, msg) \
	if((ptr) == NULL) \
	{ \
		FEUR_TEST_LOG_ERROR_MSG(msg); \
		return FEUR_Test_Failed; \
	} else {}

#define FEUR_TEST_ASSERT_FLOAT_MSG(a, b, msg) \
	if(fabsf((a) - (b)) > EPSILON) \
	{ \
		FEUR_TEST_LOG_ERROR_MSG(msg); \
		return FEUR_Test_Failed; \
	} else {}

#endif // FEUR_TEST_ASSERT_H
