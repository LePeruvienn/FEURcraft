#ifndef UTILS_PTR_HELPER_H
#define UTILS_PTR_HELPER_H

#define FREE_PTR_NOT_NULL(ptr, free_func) \
	if (ptr != NULL) \
	{ \
		free_func(ptr); \
		ptr = NULL; \
	}

#endif // UTILS_PTR_HELPER_H
