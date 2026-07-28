#include "chunk_geometry.h"

#include "geometry.h"
#include "vertex.h"
#include "vertex_layout.h"

#include "block.h"
#include "block_face.h"
#include "chunk.h"

#include "array_list.h"

#include "vec3i.h"

#include "logger.h"

#define FACE_VERTICES_AMOUNT 4
#define FACE_INDICES_AMOUNT 6

// TODO !!
static void chunk_geometry_add_block_face(Geometry* geometry,
                                          Block /* block */, BlockFace /*face*/,
                                          Vec3i /* pos*/)
{
	VertexBlock vertices_buffer[FACE_VERTICES_AMOUNT] = { 0 };

	
	unsigned int indices_buffer[FACE_INDICES_AMOUNT] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	// Add face to buffer
	geometry_add_buffer(geometry,
	                    vertices_buffer, FACE_VERTICES_AMOUNT,
	                    indices_buffer, FACE_INDICES_AMOUNT);
}

Geometry* chunk_geometry_create(const Chunk* chunk)
{
	VertexLayout vertex_layout;
	vertex_layout_init_default_block(&vertex_layout);

	Geometry* chunk_geometry = geometry_create_empty(vertex_layout);

	for (size_t i = 0; i < CHUNK_SIZE; ++i)
	{
		Block block = chunk_get_block_from_index(chunk, i);

		if (block == BLOCK_AIR)
		{
			continue;
		}

		Vec3i pos = chunk_block_pos(i);

		Vec3i pos_top   = VEC3I(pos.x,     pos.y,     pos.z + 1);
		Vec3i pos_bot   = VEC3I(pos.x,     pos.y,     pos.z - 1);
		Vec3i pos_front = VEC3I(pos.x,     pos.y + 1, pos.z    );
		Vec3i pos_back  = VEC3I(pos.x,     pos.y - 1, pos.z    );
		Vec3i pos_left  = VEC3I(pos.x - 1, pos.y,     pos.z    );
		Vec3i pos_right = VEC3I(pos.x + 1, pos.y,     pos.z    );

		if (chunk_get_block_from_pos(chunk, pos_top) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_TOP, pos);
		}
		if (chunk_get_block_from_pos(chunk, pos_bot) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_BOT, pos);
		}
		if (chunk_get_block_from_pos(chunk, pos_front) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_FRONT, pos);
		}
		if (chunk_get_block_from_pos(chunk, pos_back) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_BACK, pos);
		}
		if (chunk_get_block_from_pos(chunk, pos_left) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_LEFT, pos);
		}
		if (chunk_get_block_from_pos(chunk, pos_right) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_RIGHT, pos);
		}
	}

	// If chunk is empty dont return a geometry.
	if (chunk_geometry->vertices->count == 0)
	{
		LOG_WARNING("Not returning geometry cause chunk has no vertices");
		geometry_free(chunk_geometry);
		return NULL;
	}

	return chunk_geometry;
}

