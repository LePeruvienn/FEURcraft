#ifndef COMPONENT_HANDLE_H
#define COMPONENT_HANDLE_H

#include "feur_types.h"

#define COMPONENT_HANDLE(_index, _generation) \
	((ComponentHandle) { .index = (_index), .generation = (_generation) })

typedef struct ComponentHandle ComponentHandle;

struct ComponentHandle
{
	uint index;
	uint generation;
};

#endif // COMPONENT_HANDLE_H
