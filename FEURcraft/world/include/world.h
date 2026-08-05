#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"

#include "vec3.h"

#define WORLD_CHUNK_LOAD_DISTANCE 5

#define WORLD_CHUNK_SIZE \
	(WORLD_CHUNK_LOAD_DISTANCE * WORLD_CHUNK_LOAD_DISTANCE)

typedef enum ChunkState ChunkState;

enum ChunkState
{
	CHUNK_NOT_LOADED = 0,
	CHUNK_DIRTY,
	CHUNK_OK
};

typedef struct World World;

struct World
{
	Vec3 origin;

	Chunk loaded_chunks[WORLD_CHUNK_SIZE];
	ChunkState chunks_status[WORLD_CHUNK_SIZE];
};

void world_init(World* world);

void world_update(World* world, Vec3 origin);

#endif // WORLD_H
