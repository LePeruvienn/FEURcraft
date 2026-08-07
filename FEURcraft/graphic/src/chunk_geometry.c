#include "chunk_geometry.h"

#include "geometry.h"
#include "geometry_data.h"
#include "vertex.h"
#include "vertex_layout.h"

#include "block.h"
#include "block_face.h"
#include "chunk.h"

#include "array_list.h"

#include "vec3i.h"

#include "logger.h"
#include "error_checker.h"

#include <string.h>

static void chunk_geometry_add_block_face(Geometry* geometry,
                                          Block block, BlockFace face,
                                          Vec3i pos)
{
	CHECK_COND_RET_WARN(block != BLOCK_AIR, "Cannot add a BLOCK_AIR face.", );

	VertexBlock vertices_buffer[BLOCK_FACE_VERTICES_AMOUNT] = { 0 };

	geometry_data_get_block_face_vertices(face, vertices_buffer);

	unsigned int layer_index = (block - 1) * BLOCK_FACE_COUNT;

	// Applying chunk pos, and layer_index to vertices
	for(unsigned int i = 0; i < BLOCK_FACE_VERTICES_AMOUNT; ++i)
	{
		// vertices_buffer already contain the face id value
		// TextureArray index = (block * BLOCK_FACE_COUNT) + BlockFace id;
		vertices_buffer[i].layer_index += layer_index;

		// apply chunk_pos offset
		vec3_add_in(&vertices_buffer[i].pos, VEC3(pos.x, pos.y, pos.z));
	}

	// Add face to buffer
	geometry_add_buffer(geometry,    vertices_buffer, BLOCK_FACE_VERTICES_AMOUNT,
	                              BLOCK_FACE_INDICES, BLOCK_FACE_INDICES_AMOUNT);
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

		// Y UP !!!
		Vec3i pos_top   = VEC3I(pos.x,     pos.y + 1, pos.z    );
		Vec3i pos_bot   = VEC3I(pos.x,     pos.y - 1, pos.z    );
		Vec3i pos_front = VEC3I(pos.x,     pos.y,     pos.z + 1);
		Vec3i pos_back  = VEC3I(pos.x,     pos.y,     pos.z - 1);
		Vec3i pos_left  = VEC3I(pos.x - 1, pos.y,     pos.z    );
		Vec3i pos_right = VEC3I(pos.x + 1, pos.y,     pos.z    );

		// very very very naive chunk meshing for the moment
		if (!chunk_is_pos_valid(pos_top) || chunk_get_block_from_pos(chunk, pos_top) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_TOP, pos);
		}
		if (!chunk_is_pos_valid(pos_bot) || chunk_get_block_from_pos(chunk, pos_bot) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_BOT, pos);
		}
		if (!chunk_is_pos_valid(pos_front) || chunk_get_block_from_pos(chunk, pos_front) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_FRONT, pos);
		}
		if (!chunk_is_pos_valid(pos_back) || chunk_get_block_from_pos(chunk, pos_back) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_BACK, pos);
		}
		if (!chunk_is_pos_valid(pos_left) || chunk_get_block_from_pos(chunk, pos_left) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_LEFT, pos);
		}
		if (!chunk_is_pos_valid(pos_right) || chunk_get_block_from_pos(chunk, pos_right) == BLOCK_AIR)
		{
			chunk_geometry_add_block_face(chunk_geometry, block, BLOCK_FACE_RIGHT, pos);
		}
	}

	// If chunk is empty dont return a geometry.
	if (chunk_geometry->vertices->length == 0)
	{
		LOG_WARNING("Not returning geometry cause chunk has no vertices");
		geometry_free(chunk_geometry);
		return NULL;
	}

	return chunk_geometry;
}

