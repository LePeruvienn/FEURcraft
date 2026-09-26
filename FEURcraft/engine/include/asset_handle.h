#ifndef ASSET_HANDLE_H
#define ASSET_HANDLE_H

#include <stddef.h>

struct AssetHandle
{
	const char* file_path;
	size_t generation;
};

#endif // ASSET_HANDLE_H
