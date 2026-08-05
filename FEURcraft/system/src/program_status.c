#include "program_status.h"
#include "logger.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define CALLSTACK_SYMBOLS_ARRAY_SIZE 100

#ifdef __linux__

	#include <execinfo.h>
	#include <unistd.h>

	void print_call_stack()
	{
		void* symbols_array[CALLSTACK_SYMBOLS_ARRAY_SIZE];

		size_t symbols_amount = backtrace(symbols_array, CALLSTACK_SYMBOLS_ARRAY_SIZE);

		char** strings = backtrace_symbols(symbols_array, CALLSTACK_SYMBOLS_ARRAY_SIZE);

		if (strings == NULL)
		{
			LOG_WARNING("Could not get current call stack.");
			return;
		}

		LOG_INFO("Printing callstack ...");

		for (size_t i = 1; i < symbols_amount; ++i)
		{
			*(strchr(strings[i], '+')) = ' ';
			LOG("[%zu] : %s", i, strchr(strings[i], '('));
		}

		LOG_INFO("Callstack END.");

		free(strings);
	}


#else

	void print_call_stack()
	{
		LOG_INFO("Printing callstack is not avaible in your OS.");
	}
#endif
