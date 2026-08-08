#ifndef COMPONENT_STATUS_H
#define COMPONENT_STATUS_H

#include "feur_types.h"

#include <stdbool.h>

typedef struct ComponentStatus ComponentStatus;

struct ComponentStatus
{
	uint owner_id;
	uint generation;
	bool is_alive;
};

#endif // COMPONENT_STATUS_H
