#ifndef FEUR_TEST_DATA_H
#define FEUR_TEST_DATA_H

#include <stdbool.h>
#include <stdint.h>

#define FEUR_TEST_MAX_AMOUNT 128

typedef enum FEUR_Test_Result FEUR_Test_Result;

typedef struct FEUR_Test FEUR_Test;
typedef struct FEUR_Test_Group FEUR_Test_Group;
typedef struct FEUR_Tester FEUR_Tester;

enum FEUR_Test_Result
{
	FEUR_Test_Success = 0,
	FEUR_Test_Failed,
	FEUR_Test_Memory_Error
};

struct FEUR_Test
{
	const char* name;

	FEUR_Test_Result (*test_func)(void);

	bool has_run;
	bool has_failed;

	FEUR_Test_Result result;
};

struct FEUR_Test_Group
{
	const char* name;

	uint32_t test_amount;
	uint32_t failed_amount;

	FEUR_Test tests[FEUR_TEST_MAX_AMOUNT];
};

#endif // FEUR_TEST_DATA_H
