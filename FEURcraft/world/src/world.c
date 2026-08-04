#include "world.h"
#include "chunk.h"
#include "block.h"

#include "vec3.h"

#include <stddef.h>

void world_init(World* world)
{
	world->origin = VEC3_ZERO;

	for (size_t i = 0; i < WORLD_CHUNK_SIZE; ++i)
	{
		Chunk* chunk = &world->loaded_chunks[i];

		chunk_fill_all(chunk, BLOCK_AIR);
		
		world->chunks_status[i] = CHUNK_NOT_LOADED;
	}
}

void world_update(World* world, Vec3 origin)
{
	
}

