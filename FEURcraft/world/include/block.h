#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>

typedef uint8_t Block;

enum Block
{
	BLOCK_AIR  = 0,
	BLOCK_DIRT,
	BLOCK_STONE,

	BLOCK_COUNT
};

#endif // BLOCK_H
