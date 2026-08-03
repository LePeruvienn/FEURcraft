#include "geometry_data.h"

#include "vertex.h"
#include "vec3.h"
#include "block_face.h"

#include "logger.h"

#include <string.h>

const Vertex CUBE_VERTICES[CUBE_VERTICES_AMOUNT] =
{
	// Front face
	{ .pos = {{{-0.5, -0.5,  0.5}}} },
	{ .pos = {{{ 0.5, -0.5,  0.5}}} },
	{ .pos = {{{ 0.5,  0.5,  0.5}}} },
	{ .pos = {{{-0.5,  0.5,  0.5}}} },

	// Back face
	{ .pos = {{{-0.5, -0.5, -0.5}}} },
	{ .pos = {{{ 0.5, -0.5, -0.5}}} },
	{ .pos = {{{ 0.5,  0.5, -0.5}}} },
	{ .pos = {{{-0.5,  0.5, -0.5}}} }
};

const unsigned int CUBE_INDICES[CUBE_INDICES_AMOUNT] =
{
	// Front
	0, 1, 2,
	2, 3, 0,
	// Right
	1, 5, 6,
	6, 2, 1,

	// Back
	5, 4, 7,
	7, 6, 5,

	// Left
	4, 0, 3,
	3, 7, 4,

	// Top
	3, 2, 6,
	6, 7, 3,

	// Bottom
	4, 5, 1,
	1, 0, 4
};

const VertexUV CUBE_UV_VERTICES[CUBE_UV_VERTICES_AMOUNT] =
{
	// Front
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}} },
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}} },

	// Back
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}} },
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}} },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}} },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}} },

	// Top
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}} },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}} },

	// Bot
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}} },
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}} },

	// Left
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}} },
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}} },
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}} },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}} },

	// Right
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}} },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}} },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}} },
};

const unsigned int CUBE_UV_INDICES[CUBE_UV_INDICES_AMOUNT] =
{
	// Front
	0, 1, 2,
	2, 3, 0,

	// Back
	4, 5, 6,
	6, 7, 4,

	// Top
	8, 9, 10,
	10, 11, 8,

	// Bot
	12, 13, 14,
	14, 15, 12,

	// Left
	16, 17, 18,
	18, 19, 16,

	// Right
	20, 21, 22,
	22, 23, 20
};

const VertexBlock BLOCK_VERTICES[BLOCK_VERTICES_AMOUNT] =
{
	// Front
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_FRONT },
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_FRONT },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_FRONT },
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_FRONT },

	// Back
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BACK },
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BACK },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BACK },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BACK },

	// Top
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_TOP },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_TOP },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_TOP },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_TOP },

	// Bot
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BOT },
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BOT },
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BOT },
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BOT },

	// Left
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_LEFT },
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_LEFT },
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_LEFT },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_LEFT },

	// Right
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
};

const unsigned int BLOCK_INDICES[BLOCK_INDICES_AMOUNT] =
{
	// Front
	0, 1, 2,
	2, 3, 0,

	// Back
	4, 5, 6,
	6, 7, 4,

	// Top
	8, 9, 10,
	10, 11, 8,

	// Bot
	12, 13, 14,
	14, 15, 12,

	// Left
	16, 17, 18,
	18, 19, 16,

	// Right
	20, 21, 22,
	22, 23, 20
};

const VertexBlock BLOCK_FACE_FRONT_VERTICES[BLOCK_FACE_VERTICES_AMOUNT] =
{
	// Front
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_FRONT },
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_FRONT },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_FRONT },
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_FRONT }
};

const VertexBlock BLOCK_FACE_BACK_VERTICES[BLOCK_FACE_VERTICES_AMOUNT] =
{
	// Back
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BACK },
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BACK },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BACK },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BACK }
};

const VertexBlock BLOCK_FACE_TOP_VERTICES[BLOCK_FACE_VERTICES_AMOUNT] =
{
	// Top
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_TOP },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_TOP },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_TOP },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_TOP }
};

const VertexBlock BLOCK_FACE_BOT_VERTICES[BLOCK_FACE_VERTICES_AMOUNT] =
{
	// Bot
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BOT },
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_BOT },
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BOT },
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_BOT }
};

const VertexBlock BLOCK_FACE_LEFT_VERTICES[BLOCK_FACE_VERTICES_AMOUNT] =
{
	// Left
	{ .pos = {{{-0.5f, -0.5f, -0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_LEFT },
	{ .pos = {{{-0.5f, -0.5f,  0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_LEFT },
	{ .pos = {{{-0.5f,  0.5f,  0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_LEFT },
	{ .pos = {{{-0.5f,  0.5f, -0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_LEFT }
};

const VertexBlock BLOCK_FACE_RIGHT_VERTICES[BLOCK_FACE_VERTICES_AMOUNT] =
{
	// Right
	{ .pos = {{{ 0.5f, -0.5f,  0.5f}}}, .uv = {{{0.0f, 0.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
	{ .pos = {{{ 0.5f, -0.5f, -0.5f}}}, .uv = {{{1.0f, 0.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
	{ .pos = {{{ 0.5f,  0.5f, -0.5f}}}, .uv = {{{1.0f, 1.0f}}}, .layer_index = BLOCK_FACE_RIGHT },
	{ .pos = {{{ 0.5f,  0.5f,  0.5f}}}, .uv = {{{0.0f, 1.0f}}}, .layer_index = BLOCK_FACE_RIGHT }
};

const unsigned int BLOCK_FACE_INDICES[BLOCK_FACE_INDICES_AMOUNT] =
{
	0, 1, 2,
	2, 3, 0
};

void geometry_data_get_block_face_vertices(BlockFace face, VertexBlock* out_vertices_buffer)
{
	size_t size_in_bytes = BLOCK_FACE_VERTICES_AMOUNT * sizeof(VertexBlock);

	switch (face)
	{
		case BLOCK_FACE_TOP:
			memcpy(out_vertices_buffer, BLOCK_FACE_TOP_VERTICES, size_in_bytes);
			break;

		case BLOCK_FACE_BOT:
			memcpy(out_vertices_buffer, BLOCK_FACE_BOT_VERTICES, size_in_bytes);
			break;
			
		case BLOCK_FACE_FRONT:
			memcpy(out_vertices_buffer, BLOCK_FACE_FRONT_VERTICES, size_in_bytes);
			break;

		case BLOCK_FACE_BACK:
			memcpy(out_vertices_buffer, BLOCK_FACE_BACK_VERTICES, size_in_bytes);
			break;

		case BLOCK_FACE_LEFT:
			memcpy(out_vertices_buffer, BLOCK_FACE_LEFT_VERTICES, size_in_bytes);
			break;

		case BLOCK_FACE_RIGHT:
			memcpy(out_vertices_buffer, BLOCK_FACE_RIGHT_VERTICES, size_in_bytes);
			break;
		
		default:
			LOG_ERROR("Tried to get unkown face vertices buffer");
			return;
	}
}

