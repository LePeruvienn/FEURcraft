#ifndef CALL_ONCE_H
#define CALL_ONCE_H

#include <stdbool.h>

#define CALL_ONCE(id, todo) \
	do \
	{ \
		static bool _is_called_##id = false; \
		if (_is_called_##id == false) \
		{ \
			_is_called_##id = true; \
			todo; \
		} \
	} while (0)

#define CALL_ONCE_UNIQUE(todo) CALL_ONCE(unique, todo)

#endif // CALL_ONCE_H
