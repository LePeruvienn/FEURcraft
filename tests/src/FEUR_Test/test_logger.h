#ifndef FEUR_TEST_LOGGER_H
#define FEUR_TEST_LOGGER_H

#include "logger.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FEUR_TEST_LOGGER_ENABLED_ENV_STR "FEUR_Test_Log_Enabled"

// Enabled by default
static bool FEUR_Test_Log_Enabled = true;

#define FEUR_TEST_LOG(fmt, ...) \
	if (FEUR_Test_Log_Enabled)  \
		{ LOG_HEADER(stdout, "FEUR TEST", fmt, ##__VA_ARGS__); }

#define FEUR_TEST_LOG_INFO(fmt, ...) \
	if (FEUR_Test_Log_Enabled)        \
		{ LOG_HEADER(stdout, "FEUR TEST INFO", fmt, ##__VA_ARGS__); }

#define FEUR_TEST_LOG_WARNING(fmt, ...) \
	if (FEUR_Test_Log_Enabled)        \
		{ LOG_HEADER(stdout, "FEUR TEST WARNING", fmt, ##__VA_ARGS__); }


#define FEUR_TEST_LOG_ERROR(fmt, ...) \
	if (FEUR_Test_Log_Enabled)        \
		{ LOG_HEADER_FILE(stdout, "FEUR TEST ERROR", fmt, ##__VA_ARGS__); }

#endif // FEUR_TEST_LOGGER_H
