#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "vec3i.h"

#include <stddef.h>

#define CHUNK_LENGTH 16
#define CHUNK_HEIGHT 256

#define CHUNK_EMPTY() ((Chunk) { .blocks = { 0 } })

typedef struct Chunk Chunk;

struct Chunk
{
	Block blocks[CHUNK_LENGTH * CHUNK_LENGTH * CHUNK_HEIGHT];
};


size_t chunk_index(Vec3i pos);

void chunk_set_block(Chunk* chunk, Block block, Vec3i pos);

void chunk_del_block(Chunk* chunk, Vec3i pos);

#endif // CHUNK_H
