#include "chunk.h"
#include "block.h"
#include "vec3i.h"

#include "error_checker.h"

#include <stddef.h>
#include <stdbool.h>

size_t chunk_block_index(Vec3i pos)
{
	size_t index = pos.x
	             + pos.y * CHUNK_LENGTH * CHUNK_LENGTH // Y UP !!!
	             + pos.z * CHUNK_LENGTH;

	CHECK_COND_RET(index < CHUNK_SIZE,
		"Cannot get index of an invalid Chunk position", 0);

	return index;
}

Vec3i chunk_block_pos(size_t index)
{
	CHECK_COND_RET(index < CHUNK_SIZE,
		"Cannot get pos of an invalid Chunk index", VEC3I_ZERO);

	return VEC3I(
		index % CHUNK_LENGTH,                   // x
		index / (CHUNK_LENGTH * CHUNK_LENGTH),  // y
		(index / CHUNK_LENGTH) % CHUNK_LENGTH   // z
	);
}

Block chunk_get_block_from_pos(const Chunk* chunk, Vec3i pos)
{
	CHECK_IS_NULL_RET(chunk, "Cannot get block from a NULL chunk.", BLOCK_AIR);

	CHECK_COND_RET(chunk_is_pos_valid(pos) == true,
		"Cannot get block from an invalid Chunk positon.", BLOCK_AIR);


	return chunk->blocks[chunk_block_index(pos)];
}

Block chunk_get_block_from_index(const Chunk* chunk, size_t index)
{
	CHECK_IS_NULL_RET(chunk, "Cannot get block from a NULL chunk.", BLOCK_AIR);

	CHECK_COND_RET(index < CHUNK_SIZE,
		"Cannot get block from an invalid Chunk index.", BLOCK_AIR);

	return chunk->blocks[index];
}

void chunk_set_block(Chunk* chunk, Block block, Vec3i pos)
{
	CHECK_IS_NULL_RET(chunk, "Cannot set block to a NULL chunk.", );

	CHECK_COND_RET(chunk_is_pos_valid(pos) == true,
		"Cannot set block at an invalid Chunk position.", );

	chunk->blocks[chunk_block_index(pos)] = block;
}

void chunk_del_block(Chunk* chunk, Vec3i pos)
{
	CHECK_IS_NULL_RET(chunk, "Cannot del block from a NULL chunk.", );

	CHECK_COND_RET(chunk_is_pos_valid(pos) == true,
		"Cannot del block at an invalid Chunk position.", );

	chunk->blocks[chunk_block_index(pos)] = BLOCK_AIR;
}

bool chunk_is_pos_valid(Vec3i pos)
{
	return (pos.x >= 0 && pos.x < CHUNK_LENGTH &&
	        pos.y >= 0 && pos.y < CHUNK_HEIGHT && // Y UP !!!
	        pos.z >= 0 && pos.z < CHUNK_LENGTH );
}

void chunk_fill(Chunk* chunk, Block block, size_t height)
{
	CHECK_IS_NULL_RET(chunk, "Cannot fill a NULL chunk.", );

	CHECK_COND_RET(height <= CHUNK_HEIGHT,
		"Cannot fill a Chunk more than his max height", );

	for (size_t i = 0; i < CHUNK_SIZE; ++i)
	{
		Vec3i pos = chunk_block_pos(i);

		CHECK_COND_RET(pos.y >= 0, "Given Y positon is negative.", );

		unsigned int y = (unsigned int) pos.y;

		if (y > height)
			continue;

		chunk->blocks[i] = block;
	}
}

void chunk_fill_all(Chunk* chunk, Block block)
{
	CHECK_IS_NULL_RET(chunk, "Cannot fill a NULL chunk.", );

	for (size_t i = 0; i < CHUNK_SIZE; ++i)
	{
		chunk->blocks[i] = block;
	}
}

