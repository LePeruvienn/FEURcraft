#include "component_pool.h"
#include "component_handle.h"
#include "component_status.h"

#include "array_list.h"

#include "error_checker.h"
#include "logger.h"
#include "ptr_helper.h"
#include "feur_types.h"

#include <stddef.h>
#include <limits.h>
#include <string.h>

#define POOL_CAPACITY_START 128

#define INDEX_EMPTY UINT_MAX
#define GEN_INVALID UINT_MAX

#define EMPTY_HANDLE COMPONENT_HANDLE(INDEX_EMPTY, GEN_INVALID)

ComponentPool* component_pool_create(size_t component_size)
{
	ComponentPool* pool = malloc(sizeof(ComponentPool));

	CHECK_IS_NULL_RET(pool, "Failed to malloc ComponentPool", NULL);

	pool->component_size = component_size;
	pool->components = array_list_create(component_size, POOL_CAPACITY_START);
	pool->free_indices = array_list_create(sizeof(uint), POOL_CAPACITY_START);
	pool->states = array_list_create(sizeof(ComponentStatus), POOL_CAPACITY_START);

	if (pool->components  == NULL ||
	    pool->free_indices   == NULL ||
	    pool->states == NULL )
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
	FREE_PTR_NOT_NULL(pool->states,  array_list_free);

	free(pool);
}

size_t component_pool_get_length(ComponentPool* pool)
{
	CHECK_IS_NULL_RET(pool, "Cannot get size of a NULL ComponentPool", 0);

	CHECK_COND_RET(pool->components->length == pool->states->length,
		"ComponentPool components and states size mistmatch", 0);

	return pool->components->length;
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

	CHECK_COND_RET(pool->components->length == pool->states->length,
		"ComponentPool components states mistmatch.", NULL);

	ComponentStatus* status = array_list_get(pool->states, handle.index);

	CHECK_IS_NULL_RET(status, "Failed to get pool components state.", NULL);

	if (status->generation != handle.generation || status->is_alive == false)
	{
		return NULL;
	}

	return array_list_get(pool->components, handle.index);
}

ComponentHandle component_pool_new(ComponentPool* pool, uint owner_id)
{
	CHECK_IS_NULL_RET(pool,
		"Cannot create new component in a NULL ComponentPool", EMPTY_HANDLE);

	CHECK_COND_RET(pool->components->length == pool->states->length,
		"ComponentPool components states mistmatch.", EMPTY_HANDLE);

	uint free_index = INDEX_EMPTY;
	bool have_free_index = array_list_pop_uint(pool->free_indices, &free_index);

	if (have_free_index)
	{
		ComponentStatus* state = array_list_get(pool->states, free_index);

		// If we can get generation of free index we are cooked
		CHECK_IS_NULL_RET(state, 
			"Failed to get status of free_index", EMPTY_HANDLE);

		CHECK_COND_RET(state->is_alive == false,
			"ComponentStatus of free index is alive ?", EMPTY_HANDLE);

		// reseting component data
		void* component = array_list_get(pool->components, free_index);

		CHECK_IS_NULL_RET(component, "Failed to get free component", EMPTY_HANDLE);

		memset(component, 0, pool->component_size);

		// Update component state
		state->owner_id = owner_id;
		state->is_alive = true;
		++state->generation;

		// If we reach the max valid gen, we reset to 0
		if (state->generation == GEN_INVALID)
		{
			LOG_WARNING("Needed to reset generation to 0 on new component!!");
			state->generation = 0;
		}
		return COMPONENT_HANDLE(free_index, state->generation);
	}

	bool new_comp_ok = array_list_push_new(pool->components);

	CHECK_COND_RET(new_comp_ok == true,
		"Failed to push a new component to ComponentPool", EMPTY_HANDLE);

	bool new_state_ok = array_list_push_new(pool->states);

	if (new_state_ok == false)
	{
		LOG_ERROR("Failed to push a new state to ComponentPool");
		array_list_pop(pool->components, NULL);
		return EMPTY_HANDLE;
	}

	// Check if we are cooked
	CHECK_COND_RET(pool->components->length == pool->states->length,
		"Components and generation not the same size.", EMPTY_HANDLE);

	// getting last index (that is the index of the thing we pushed)
	uint new_index = pool->components->length - 1;

	ComponentStatus* new_status = array_list_get(pool->states, new_index);

	CHECK_IS_NULL_RET(new_status, 
		"Failed to get last component state", EMPTY_HANDLE);

	new_status->generation = 0;
	new_status->is_alive = true;
	new_status->owner_id = owner_id;

	return COMPONENT_HANDLE(new_index, new_status->generation);
}

void component_pool_delete(ComponentPool* pool, ComponentHandle handle)
{
	CHECK_IS_NULL_RET(pool,
		"Cannot delete component in a NULL ComponentPool", );

	// If we cant get the component:
	// - handle Invalid or already deleted
	if(component_pool_get(pool, handle) == NULL)
	{
		LOG_WARNING("Tried to delete an invalid / already deleted component");
		return;
	}

	ComponentStatus* status = array_list_get(pool->states, handle.index);

	CHECK_IS_NULL_RET(status, "Failed to get component status", );

	status->is_alive = false;

	// adding index to free indices
	CHECK_COND_RET(array_list_push(pool->free_indices, &handle.index),
		"Failed to push new_free indice, data would not be reused", );
}

