#include "component_pool.h"
#include "component_handle.h"
#include "array_list.h"

#include "error_checker.h"
#include "logger.h"
#include "ptr_helper.h"
#include "feur_types.h"

#include <stddef.h>
#include <limits.h>

#define POOL_CAPACITY_START 128

#define INDEX_EMPTY UINT_MAX
#define GEN_INVALID UINT_MAX

#define EMPTY_HANDLE COMPONENT_HANDLE(INDEX_EMPTY, GEN_INVALID)

ComponentPool* create_component_pool(size_t component_size)
{
	ComponentPool* pool = malloc(sizeof(ComponentPool));

	CHECK_IS_NULL_RET(pool, "Failed to malloc ComponentPool", NULL);

	pool->components = array_list_create(component_size, POOL_CAPACITY_START);

	pool->free_indices = array_list_create(sizeof(uint), POOL_CAPACITY_START);
	pool->generations  = array_list_create(sizeof(uint), POOL_CAPACITY_START);

	if (pool->components  == NULL ||
	    pool->free_indices   == NULL ||
	    pool->generations == NULL )
	{
		LOG_ERROR("Failed to malloc ComponentPool data");

		component_pool_free(pool);

		return NULL;
	}

	return pool;
}

void component_pool_free(ComponentPool* pool)
{
	CHECK_IS_NULL_RET(pool, "Cannot free a NULL ComponentPool", );

	FREE_PTR_NOT_NULL(pool->components,   array_list_free);
	FREE_PTR_NOT_NULL(pool->free_indices, array_list_free);
	FREE_PTR_NOT_NULL(pool->generations,  array_list_free);

	free(pool);
}

void* component_pool_get(ComponentPool* pool, ComponentHandle handle)
{
	CHECK_IS_NULL_RET(pool, "Cannot get from a NULL ComponentPool.", NULL);

	if(handle.index == INDEX_EMPTY)
	{
		return NULL;
	}

	CHECK_COND_RET(pool->components->length > handle.index,
		"Invalid ComponentPool Index", NULL);

	uint gen_index = INDEX_EMPTY;

	CHECK_COND_RET(array_list_get_uint(pool->generations, handle.index, &gen_index),
		"Failed to get generation of the current component.", NULL);

	// This means the index is not valid anymore
	// The component has been reused
	if (gen_index != handle.generation)
	{
		return NULL;
	}

	return array_list_get(pool->components, handle.index);
}

ComponentHandle component_pool_new(ComponentPool* pool)
{
	CHECK_IS_NULL_RET(pool,
		"Cannot create new component in a NULL ComponentPool", EMPTY_HANDLE);

	uint free_index = INDEX_EMPTY;
	bool have_free_index = array_list_pop_uint(pool->free_indices, &free_index);

	if (have_free_index)
	{
		uint* cur_gen = array_list_get(pool->generations, free_index);

		// If we can get generation of free index we are cooked
		CHECK_IS_NULL_RET(cur_gen,
			"Failed to get generation of free_index", EMPTY_HANDLE);

		return COMPONENT_HANDLE(free_index, *cur_gen);
	}

	// If we dont have free_index we make a new component + his generation
	CHECK_COND_RET(array_list_push_new(pool->components),
		"Failed to push new component", EMPTY_HANDLE);

	CHECK_COND_RET(array_list_push_new(pool->generations),
		"Failed to push new generation", EMPTY_HANDLE);

	// Check if we are cooked
	CHECK_COND_RET(pool->components->length == pool->generations->length,
		"Components and generation not the same size.", EMPTY_HANDLE);

	// getting last index (that is the index of the thing we pushed)
	uint new_index = pool->components->length - 1;

	uint* new_gen = (uint*) array_list_get(pool->generations, new_index);

	CHECK_IS_NULL_RET(new_gen, "Failed to get last generation", EMPTY_HANDLE);

	// Set generation to 0
	*new_gen = 0;

	return COMPONENT_HANDLE(new_index, *new_gen);
}

void component_pool_delete(ComponentPool* pool, ComponentHandle handle)
{
	CHECK_IS_NULL_RET(pool,
		"Cannot create new component in a NULL ComponentPool", );

	// If we cant get the component:
	// - handle Invalid or already deleted
	if(component_pool_get(pool, handle) == NULL)
	{
		LOG_WARNING("Tried to delete an invalid / already deleted component");
		return;
	}

	uint* cur_gen = array_list_get(pool->generations, handle.index);

	// Incrementing generation
	(*cur_gen)++;
	
	// If we reach the max valid gen, we reset to 0
	if (*cur_gen == GEN_INVALID)
	{
		LOG_WARNING("Needed to reset generation to 0 on new component!!");
		*cur_gen = 0;
	}

	// adding index to free indices
	array_list_push(pool->free_indices, &handle.index);
}

