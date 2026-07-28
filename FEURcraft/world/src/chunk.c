#include "chunk.h"
#include "block.h"
#include "vec3i.h"

#include <stddef.h>

size_t chunk_block_index(Vec3i pos)
{
	return pos.x
	     + pos.z * CHUNK_LENGTH
	     + pos.y * CHUNK_LENGTH * CHUNK_LENGTH;
}

Vec3i chunk_block_pos(size_t index)
{
	return VEC3I(
		index % CHUNK_LENGTH,                  // x
		(index / CHUNK_LENGTH) % CHUNK_LENGTH, // y
		index / (CHUNK_LENGTH * CHUNK_LENGTH)  // z
	);
}

Block chunk_get_block_from_pos(const Chunk* chunk, Vec3i pos)
{
	return chunk->blocks[chunk_block_index(pos)];
}

Block chunk_get_block_from_index(const Chunk* chunk, size_t index)
{
	return chunk->blocks[index];
}

void chunk_set_block(Chunk* chunk, Block block, Vec3i pos)
{
	chunk->blocks[chunk_block_index(pos)] = block;
}

void chunk_del_block(Chunk* chunk, Vec3i pos)
{
	chunk->blocks[chunk_block_index(pos)] = 0;
}

