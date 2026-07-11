#include "FEUR_Test/FEUR_Test.h"

#include <stdlib.h>

FEUR_Test_Result Test_Integer(void)
{
	int value = 10;

	FEUR_TEST_ASSERT(value == 10);
	FEUR_TEST_ASSERT(value != 5);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Pointer(void)
{
	int* ptr = NULL;

	FEUR_TEST_ASSERT_NULL(ptr);

	ptr = malloc(sizeof(int));

	FEUR_TEST_ASSERT_NOT_NULL(ptr);

	free(ptr);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Float(void)
{
	float value = 0.333333f;

	FEUR_TEST_ASSERT_FLOAT(value, 0.333333f);

	return FEUR_Test_Success;
}


FEUR_Test_Result Test_Failing(void)
{
	int value = 5;

	FEUR_TEST_ASSERT(value == 10);

	return FEUR_Test_Success;
}


int main(void)
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("This is a example of log in a test!");

	FEUR_Test_Add_Group("Easy Tests :)");

	FEUR_Test_Add_Test("Integer Assert", Test_Integer);
	FEUR_Test_Add_Test("Pointer Assert", Test_Pointer);

	FEUR_Test_Add_Group("Hard Tests D:");

	FEUR_Test_Add_Test("Float Assert", Test_Float);
	FEUR_Test_Add_Test("Failing Assert", Test_Failing);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
