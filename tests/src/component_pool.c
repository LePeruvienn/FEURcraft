#include "FEUR_Test/FEUR_Test.h"

#include "component_pool.h"

#include <stddef.h>

typedef struct TestComponent TestComponent;

struct TestComponent
{
	int id;
	float health;
	float damage;
};

FEUR_Test_Result Test_ComponentPool_Create_Free()
{
	ComponentPool* pool = create_component_pool(sizeof(TestComponent));

	FEUR_TEST_ASSERT_EQUAL(pool != NULL, true);
	FEUR_TEST_ASSERT_EQUAL(pool->components != NULL, true);
	FEUR_TEST_ASSERT_EQUAL(pool->free_indices != NULL, true);
	FEUR_TEST_ASSERT_EQUAL(pool->generations != NULL, true);

	component_pool_free(pool);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ComponentPool_New_Get()
{
	ComponentPool* pool = create_component_pool(sizeof(TestComponent));

	ComponentHandle handle = component_pool_new(pool);
	
	TestComponent* comp = (TestComponent*)component_pool_get(pool, handle);
	FEUR_TEST_ASSERT_EQUAL(comp != NULL, true);

	comp->id = 1;
	comp->health = 100.0f;
	comp->damage = 15.5f;

	TestComponent* comp_check = (TestComponent*)component_pool_get(pool, handle);
	FEUR_TEST_ASSERT_EQUAL(comp_check->id, 1);
	FEUR_TEST_ASSERT_FLOAT(comp_check->health, 100.0f);
	FEUR_TEST_ASSERT_FLOAT(comp_check->damage, 15.5f);

	component_pool_free(pool);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ComponentPool_Delete()
{
	ComponentPool* pool = create_component_pool(sizeof(TestComponent));

	ComponentHandle handle = component_pool_new(pool);
	
	TestComponent* comp = (TestComponent*)component_pool_get(pool, handle);
	FEUR_TEST_ASSERT_EQUAL(comp != NULL, true);

	component_pool_delete(pool, handle);

	TestComponent* comp_after_delete = (TestComponent*)component_pool_get(pool, handle);
	FEUR_TEST_ASSERT_EQUAL(comp_after_delete == NULL, true);

	component_pool_free(pool);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ComponentPool_Generations()
{
	ComponentPool* pool = create_component_pool(sizeof(TestComponent));

	ComponentHandle handle1 = component_pool_new(pool);
	
	TestComponent* comp1 = (TestComponent*)component_pool_get(pool, handle1);
	comp1->id = 42;

	component_pool_delete(pool, handle1);

	ComponentHandle handle2 = component_pool_new(pool);

	TestComponent* comp1_old = (TestComponent*)component_pool_get(pool, handle1);
	FEUR_TEST_ASSERT_EQUAL(comp1_old == NULL, true);

	TestComponent* comp2 = (TestComponent*)component_pool_get(pool, handle2);
	FEUR_TEST_ASSERT_EQUAL(comp2 != NULL, true);
	comp2->id = 84;

	FEUR_TEST_ASSERT_EQUAL(comp2->id, 84);

	component_pool_free(pool);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_ComponentPool_Stress()
{
	ComponentPool* pool = create_component_pool(sizeof(TestComponent));

	ComponentHandle handles[100];

	for (int i = 0; i < 100; ++i)
	{
		handles[i] = component_pool_new(pool);
		TestComponent* comp = (TestComponent*)component_pool_get(pool, handles[i]);
		comp->id = i;
	}

	for (int i = 0; i < 100; ++i)
	{
		TestComponent* comp = (TestComponent*)component_pool_get(pool, handles[i]);
		FEUR_TEST_ASSERT_EQUAL(comp != NULL, true);
		FEUR_TEST_ASSERT_EQUAL(comp->id, i);
	}

	for (int i = 0; i < 100; i += 2)
	{
		component_pool_delete(pool, handles[i]);
	}

	for (int i = 0; i < 100; ++i)
	{
		TestComponent* comp = (TestComponent*)component_pool_get(pool, handles[i]);
		if (i % 2 == 0)
		{
			FEUR_TEST_ASSERT_EQUAL(comp == NULL, true);
		}
		else
		{
			FEUR_TEST_ASSERT_EQUAL(comp != NULL, true);
			FEUR_TEST_ASSERT_EQUAL(comp->id, i);
		}
	}

	component_pool_free(pool);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("Lifecycle");
	FEUR_Test_Add_Test("Create Free", Test_ComponentPool_Create_Free);

	FEUR_Test_Add_Group("Operations");
	FEUR_Test_Add_Test("New Get", Test_ComponentPool_New_Get);
	FEUR_Test_Add_Test("Delete", Test_ComponentPool_Delete);
	FEUR_Test_Add_Test("Generations Reusability", Test_ComponentPool_Generations);
	FEUR_Test_Add_Test("Stress Test", Test_ComponentPool_Stress);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}

