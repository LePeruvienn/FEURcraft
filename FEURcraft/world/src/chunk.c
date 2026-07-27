#include "chunk.h"
#include "block.h"
#include "vec3i.h"

#include <stddef.h>

size_t chunk_index(Vec3i pos)
{
	return pos.x
	     + pos.z * CHUNK_LENGTH
	     + pos.y * CHUNK_LENGTH * CHUNK_LENGTH;
}

void chunk_set_block(Chunk* chunk, Block block, Vec3i pos)
{
	chunk->blocks[chunk_index(pos)] = block;
}

void chunk_del_block(Chunk* chunk, Vec3i pos)
{
	chunk->blocks[chunk_index(pos)] = 0;
}

