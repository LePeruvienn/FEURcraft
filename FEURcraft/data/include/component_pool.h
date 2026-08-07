#ifndef COMPONENT_POOL_H
#define COMPONENT_POOL_H

#include "component_handle.h"

#include "array_list.h"

#include <stddef.h>

typedef struct ComponentPool ComponentPool;

struct ComponentPool
{
	ArrayList* components;
	ArrayList* free_indices;
	ArrayList* generations;
};

ComponentPool* create_component_pool(size_t component_size);

void component_pool_free(ComponentPool* pool);

void* component_pool_get(ComponentPool* pool, ComponentHandle handle);

ComponentHandle component_pool_new(ComponentPool* pool);

void component_pool_delete(ComponentPool* pool, ComponentHandle handle);

#endif // COMPONENT_POOL_H
