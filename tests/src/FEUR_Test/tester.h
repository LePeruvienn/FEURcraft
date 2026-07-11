#ifndef FEUR_TEST_H
#define FEUR_TEST_H

#include "test_data.h"

#include "logger.h"
#include "ansi_colors.h"

#include "env_helper.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define FEUR_TESTS_ENABLE_MINIMAL_OUTPUT_ENV "FEUR_Tests_Enable_Minimal_Output"

#define FEUR_TEST_GROUP_MAX_AMOUNT 128

struct FEUR_Tester
{
	FEUR_Test_Group test_groups[FEUR_TEST_GROUP_MAX_AMOUNT];

	uint32_t test_group_amount;

	uint32_t test_failed_amount;
	uint32_t group_failed_amount;
};

static FEUR_Tester g_FEUR_tester = { 0 };
static bool g_FEUR_is_init = false;
static bool g_FEUR_test_running = false;

void FEUR_Test_Init()
{
	if(g_FEUR_is_init)
	{
		LOG_ERROR("FEUR Tests are already initialized");
		return;
	}

	g_FEUR_tester.test_group_amount   = 0;
	g_FEUR_tester.test_failed_amount  = 0;
	g_FEUR_tester.group_failed_amount = 0;

	g_FEUR_is_init = true;
}

void FEUR_Test_Add_Group(const char* name)
{
	if(g_FEUR_is_init == false)
	{
		LOG_ERROR("FEUR Tests must be initialized before adding a group.");
		return;
	}

	if(g_FEUR_test_running)
	{
		LOG_ERROR("Cannot add groups while FEUR tests are running.");
	}

	if(g_FEUR_tester.test_group_amount >= FEUR_TEST_GROUP_MAX_AMOUNT)
	{
		LOG_ERROR("FEUR Tests Maximum numbers of group reached !");
		return;
	}

	FEUR_Test_Group* test_group = &g_FEUR_tester.test_groups[g_FEUR_tester.test_group_amount];

	test_group->name = name;
	test_group->test_amount = 0;
	test_group->failed_amount = 0;

	++g_FEUR_tester.test_group_amount;
}

void FEUR_Test_Add_Test(const char* name, FEUR_Test_Result (*test_func)())
{
	if(g_FEUR_is_init == false)
	{
		LOG_ERROR("FEUR Tests must be initialized before adding a test.");
		return;
	}

	if(g_FEUR_test_running)
	{
		LOG_ERROR("Cannot add tests while FEUR tests are running.");
		return;
	}

	if(g_FEUR_tester.test_group_amount == 0)
	{
		FEUR_Test_Add_Group("FEUR Tests");
	}

	FEUR_Test_Group* test_group = &g_FEUR_tester.test_groups[g_FEUR_tester.test_group_amount - 1];

	if(test_group->test_amount >= FEUR_TEST_MAX_AMOUNT)
	{
		LOG_ERROR("Maximum numbers of FEUR tests for this group has been reached !");
		return;
	}

	FEUR_Test* test = &test_group->tests[test_group->test_amount];

	test->name = name;
	test->test_func = test_func;

	test->has_run = false;
	test->has_failed = false;
	test->result = FEUR_Test_Success;

	++test_group->test_amount;
}

void FEUR_Test_Run()
{
	g_FEUR_test_running = true;

	for(uint32_t i = 0; i < g_FEUR_tester.test_group_amount; ++i)
	{
		FEUR_Test_Group* test_group = &g_FEUR_tester.test_groups[i];

		for(uint32_t j = 0; j < test_group->test_amount; ++j)
		{
			FEUR_Test* test = &test_group->tests[j];

			test->has_run = true;
			test->result = test->test_func();

			if(test->result != FEUR_Test_Success)
			{
				test->has_failed = true;

				++test_group->failed_amount;
				++g_FEUR_tester.test_failed_amount;
			}
		}

		if(test_group->failed_amount > 0)
		{
			++g_FEUR_tester.group_failed_amount;
		}
	}
}

static void FEUR_PrintBar()
{
	printf(ANSI_COLOR_BOLD ANSI_COLOR_CYAN "============================" ANSI_COLOR_RESET "\n");
}

static void FEUR_PrintHeader()
{
	printf("\n");
	FEUR_PrintBar();

	printf(ANSI_COLOR_BOLD 
		"     ▄▖▄▖▖▖▄▖  ▄▖    ▗ \n"
		"     ▙▖▙▖▌▌▙▘  ▐ █▌▛▘▜▘\n"
		"     ▌ ▙▖▙▌▌▌  ▐ ▙▖▄▌▐▖\n"
	ANSI_COLOR_RESET);

	FEUR_PrintBar();
}

static const char* FEUR_FailColor(uint32_t failed_count)
{
	return (failed_count > 0) ? ANSI_COLOR_RED : ANSI_COLOR_GREEN;
}

void FEUR_Test_End()
{
	bool minimal_output_enabled = env_get_bool(FEUR_TESTS_ENABLE_MINIMAL_OUTPUT_ENV);

	g_FEUR_test_running = false;

	uint32_t total_tests = 0;

	if (minimal_output_enabled == false)
	{
		FEUR_PrintHeader();
	}

	for(uint32_t i = 0; i < g_FEUR_tester.test_group_amount; ++i)
	{
		FEUR_Test_Group* test_group = &g_FEUR_tester.test_groups[i];
		printf("\n" ANSI_COLOR_BOLD "[%s]" ANSI_COLOR_RESET "\n", test_group->name);

		for(uint32_t j = 0; j < test_group->test_amount; ++j)
		{
			FEUR_Test* test = &test_group->tests[j];
			++total_tests;

			if(test->has_failed)
			{
				printf("  " ANSI_COLOR_RED "[FAILED]" ANSI_COLOR_RESET " %s\n", test->name);
			}
			else
			{
				printf("  " ANSI_COLOR_GREEN "[PASS]  " ANSI_COLOR_RESET " %s\n", test->name);
			}
		}
	}

	if (minimal_output_enabled )
	{
		// We exit by the number of failed tests (0 == OK, else some FAILED !)
		EXIT_PROGRAM(g_FEUR_tester.test_failed_amount);
		return;
	}

	uint32_t passed_tests = total_tests - g_FEUR_tester.test_failed_amount;
	float pass_rate = (total_tests > 0) ? (100.0f * (float)passed_tests / (float)total_tests) : 100.0f;

	// OUI LE CODE EST DEGEULASS OUI MAIS MOI JE SUIS UN FOU MOI 🤯

	printf("\n");
	FEUR_PrintBar();
	printf("Groups : %u total, %s%u failed" ANSI_COLOR_RESET "\n",
	       g_FEUR_tester.test_group_amount,
	       FEUR_FailColor(g_FEUR_tester.group_failed_amount),
	       g_FEUR_tester.group_failed_amount);
	printf("Tests  : %u total, " ANSI_COLOR_GREEN "%u passed" ANSI_COLOR_RESET ", %s%u failed" ANSI_COLOR_RESET " (%.0f%% pass rate)\n",
	       total_tests, passed_tests,
	       FEUR_FailColor(g_FEUR_tester.test_failed_amount),
	       g_FEUR_tester.test_failed_amount,
	       pass_rate);
	FEUR_PrintBar();

	if(g_FEUR_tester.test_failed_amount == 0)
	{
		printf("\n" ANSI_COLOR_BOLD ANSI_COLOR_GREEN "Juste le/la GOAT en fait B)" ANSI_COLOR_RESET "\n");
	}

	// We exit by the number of failed tests (0 == OK, else some FAILED !)
	EXIT_PROGRAM(g_FEUR_tester.test_failed_amount);
}
#endif // FEUR_TEST_H

