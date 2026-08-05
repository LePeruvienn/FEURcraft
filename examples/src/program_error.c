#include "error_checker.h"

#define MAX_CALL_AMOUNT 5

void foo(int n);
void bar(int n);
void buzz(int n);

void foo(int n)
{
	CHECK_COND(n < MAX_CALL_AMOUNT, "Reached the maximum call amount!");

	switch(n % 2)
	{
		case 0: bar(n + 1);
			break;

		case 1: buzz(n + 1);
			break;

		default:
			LOG_ERROR("This should not happend");
	}
}

void bar(int n)
{
	CHECK_COND(n < MAX_CALL_AMOUNT, "Reached the maximum call amount!");

	switch(n % 2)
	{
		case 0: foo(n + 1);
			break;

		case 1: buzz(n + 1);
			break;

		default:
			LOG_ERROR("This should not happend");
	}
}

void buzz(int n)
{
	CHECK_COND(n < MAX_CALL_AMOUNT, "Reached the maximum call amount!");

	switch(n % 2)
	{
		case 0: foo(n + 1);
			break;

		case 1: bar(n + 1);
			break;

		default:
			LOG_ERROR("This should not happend");
	}
}

int main()
{
	foo(0);
}
