#include "program_status.h"
#include "logger.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define CALLSTACK_SYMBOLS_ARRAY_SIZE 100

#if defined(__linux__)

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

		LOG_INFO("LINUX DETECTED");
		LOG_INFO("Printing callstack ...");

		for (size_t i = 1; i < symbols_amount; ++i)
		{
			*(strchr(strings[i], '+')) = ' ';
			LOG("[%zu] : %s", i, strchr(strings[i], '('));
		}

		LOG_INFO("Callstack END.");

		free(strings);
	}

#elif defined(_WIN32)

	#include <windows.h>
	#include <dbghelp.h>
	#include <stdint.h>

	#pragma comment(lib, "dbghelp.lib")

	void print_call_stack()
	{
		HANDLE process = GetCurrentProcess();

		if (!SymInitialize(process, NULL, TRUE))
		{
			LOG_WARNING("Could not initialize DbgHelp.");
			return;
		}

		void* symbols_array[CALLSTACK_SYMBOLS_ARRAY_SIZE];

		USHORT symbols_amount = CaptureStackBackTrace(
			0,
			CALLSTACK_SYMBOLS_ARRAY_SIZE,
			symbols_array,
			NULL
		);

		LOG_INFO("WINDOWS DETECTED");
		LOG_INFO("Printing callstack ...");

		for (USHORT i = 1; i < symbols_amount; ++i)
		{
			DWORD64 address = (DWORD64)(uintptr_t)symbols_array[i];

			// SYMBOL_INFO + space for the function name.
			char buffer[sizeof(SYMBOL_INFO) + 256];

			SYMBOL_INFO* symbol = (SYMBOL_INFO*)buffer;

			memset(buffer, 0, sizeof(buffer));

			symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			symbol->MaxNameLen = 255;

			DWORD64 symbol_displacement = 0;

			if (!SymFromAddr(
					process,
					address,
					&symbol_displacement,
					symbol))
			{
				LOG("[%u] : 0x%llx",
					i,
					(unsigned long long) address);

				continue;
			}

			// Try to resolve source file + line number.
			IMAGEHLP_LINE64 line;

			memset(&line, 0, sizeof(line));

			line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

			DWORD line_displacement = 0;

			if (SymGetLineFromAddr64(
					process,
					address,
					&line_displacement,
					&line))
			{
				LOG("[%u] : %s - %s:%lu",
					i,
					symbol->Name,
					line.FileName,
					line.LineNumber);
			}
			else
			{
				// Symbols available, but source line unavailable.
				LOG("[%u] : %s + 0x%llx",
					i,
					symbol->Name,
					(unsigned long long) symbol_displacement);
			}
		}

		LOG_INFO("Callstack END.");

		SymCleanup(process);
	}

#else

	void print_call_stack()
	{
		LOG_INFO("UNKNOWN OS");
		LOG_INFO("Printing callstack is not avaible in your OS.");
	}
#endif
