#ifndef GEOMETRY_DATA_H
#define GEOMETRY_DATA_H

#include "vertex.h"
#include "vec3.h"

#define CUBE_VERTICES_AMOUNT 8
#define CUBE_INDICES_AMOUNT 36

const Vertex CUBE_VERTICES[CUBE_VERTICES_AMOUNT] =
{
	// Front face
	{ .pos = VEC3(-0.5, -0.5,  0.5) },
	{ .pos = VEC3( 0.5, -0.5,  0.5) },
	{ .pos = VEC3( 0.5,  0.5,  0.5) },
	{ .pos = VEC3(-0.5,  0.5,  0.5) },

	// Back face
	{ .pos = VEC3(-0.5, -0.5, -0.5) },
	{ .pos = VEC3( 0.5, -0.5, -0.5) },
	{ .pos = VEC3( 0.5,  0.5, -0.5) },
	{ .pos = VEC3(-0.5,  0.5, -0.5) }
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

#define CUBE_UV_VERTICES_AMOUNT 24
#define CUBE_UV_INDICES_AMOUNT 36

const VertexUV CUBE_UV_VERTICES[CUBE_UV_VERTICES_AMOUNT] =
{
	// Front
	{ .pos = VEC3(-0.5f, -0.5f,  0.5f), .uv = VEC2(0.0f, 0.0f) },
	{ .pos = VEC3( 0.5f, -0.5f,  0.5f), .uv = VEC2(1.0f, 0.0f) },
	{ .pos = VEC3( 0.5f,  0.5f,  0.5f), .uv = VEC2(1.0f, 1.0f) },
	{ .pos = VEC3(-0.5f,  0.5f,  0.5f), .uv = VEC2(0.0f, 1.0f) },

	// Back
	{ .pos = VEC3( 0.5f, -0.5f, -0.5f), .uv = VEC2(0.0f, 0.0f) },
	{ .pos = VEC3(-0.5f, -0.5f, -0.5f), .uv = VEC2(1.0f, 0.0f) },
	{ .pos = VEC3(-0.5f,  0.5f, -0.5f), .uv = VEC2(1.0f, 1.0f) },
	{ .pos = VEC3( 0.5f,  0.5f, -0.5f), .uv = VEC2(0.0f, 1.0f) },

	// Top
	{ .pos = VEC3(-0.5f,  0.5f,  0.5f), .uv = VEC2(0.0f, 0.0f) },
	{ .pos = VEC3( 0.5f,  0.5f,  0.5f), .uv = VEC2(1.0f, 0.0f) },
	{ .pos = VEC3( 0.5f,  0.5f, -0.5f), .uv = VEC2(1.0f, 1.0f) },
	{ .pos = VEC3(-0.5f,  0.5f, -0.5f), .uv = VEC2(0.0f, 1.0f) },

	// Bot
	{ .pos = VEC3(-0.5f, -0.5f, -0.5f), .uv = VEC2(0.0f, 0.0f) },
	{ .pos = VEC3( 0.5f, -0.5f, -0.5f), .uv = VEC2(1.0f, 0.0f) },
	{ .pos = VEC3( 0.5f, -0.5f,  0.5f), .uv = VEC2(1.0f, 1.0f) },
	{ .pos = VEC3(-0.5f, -0.5f,  0.5f), .uv = VEC2(0.0f, 1.0f) },

	// Left
	{ .pos = VEC3(-0.5f, -0.5f, -0.5f), .uv = VEC2(0.0f, 0.0f) },
	{ .pos = VEC3(-0.5f, -0.5f,  0.5f), .uv = VEC2(1.0f, 0.0f) },
	{ .pos = VEC3(-0.5f,  0.5f,  0.5f), .uv = VEC2(1.0f, 1.0f) },
	{ .pos = VEC3(-0.5f,  0.5f, -0.5f), .uv = VEC2(0.0f, 1.0f) },

	// Right
	{ .pos = VEC3( 0.5f, -0.5f,  0.5f), .uv = VEC2(0.0f, 0.0f) },
	{ .pos = VEC3( 0.5f, -0.5f, -0.5f), .uv = VEC2(1.0f, 0.0f) },
	{ .pos = VEC3( 0.5f,  0.5f, -0.5f), .uv = VEC2(1.0f, 1.0f) },
	{ .pos = VEC3( 0.5f,  0.5f,  0.5f), .uv = VEC2(0.0f, 1.0f) },
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


#define BLOCK_VERTICES_AMOUNT 24
#define BLOCK_INDICES_AMOUNT 36

const VertexBlock BLOCK_VERTICES[BLOCK_VERTICES_AMOUNT] =
{
	// Front
	{ .pos = VEC3(-0.5f, -0.5f,  0.5f), .uv = VEC2(0.0f, 0.0f), .face = BLOCK_FACE_FRONT },
	{ .pos = VEC3( 0.5f, -0.5f,  0.5f), .uv = VEC2(1.0f, 0.0f), .face = BLOCK_FACE_FRONT },
	{ .pos = VEC3( 0.5f,  0.5f,  0.5f), .uv = VEC2(1.0f, 1.0f), .face = BLOCK_FACE_FRONT },
	{ .pos = VEC3(-0.5f,  0.5f,  0.5f), .uv = VEC2(0.0f, 1.0f), .face = BLOCK_FACE_FRONT },

	// Back
	{ .pos = VEC3( 0.5f, -0.5f, -0.5f), .uv = VEC2(0.0f, 0.0f), .face = BLOCK_FACE_BACK },
	{ .pos = VEC3(-0.5f, -0.5f, -0.5f), .uv = VEC2(1.0f, 0.0f), .face = BLOCK_FACE_BACK },
	{ .pos = VEC3(-0.5f,  0.5f, -0.5f), .uv = VEC2(1.0f, 1.0f), .face = BLOCK_FACE_BACK },
	{ .pos = VEC3( 0.5f,  0.5f, -0.5f), .uv = VEC2(0.0f, 1.0f), .face = BLOCK_FACE_BACK },

	// Top
	{ .pos = VEC3(-0.5f,  0.5f,  0.5f), .uv = VEC2(0.0f, 0.0f), .face = BLOCK_FACE_TOP },
	{ .pos = VEC3( 0.5f,  0.5f,  0.5f), .uv = VEC2(1.0f, 0.0f), .face = BLOCK_FACE_TOP },
	{ .pos = VEC3( 0.5f,  0.5f, -0.5f), .uv = VEC2(1.0f, 1.0f), .face = BLOCK_FACE_TOP },
	{ .pos = VEC3(-0.5f,  0.5f, -0.5f), .uv = VEC2(0.0f, 1.0f), .face = BLOCK_FACE_TOP },

	// Bot
	{ .pos = VEC3(-0.5f, -0.5f, -0.5f), .uv = VEC2(0.0f, 0.0f), .face = BLOCK_FACE_BOT },
	{ .pos = VEC3( 0.5f, -0.5f, -0.5f), .uv = VEC2(1.0f, 0.0f), .face = BLOCK_FACE_BOT },
	{ .pos = VEC3( 0.5f, -0.5f,  0.5f), .uv = VEC2(1.0f, 1.0f), .face = BLOCK_FACE_BOT },
	{ .pos = VEC3(-0.5f, -0.5f,  0.5f), .uv = VEC2(0.0f, 1.0f), .face = BLOCK_FACE_BOT },

	// Left
	{ .pos = VEC3(-0.5f, -0.5f, -0.5f), .uv = VEC2(0.0f, 0.0f), .face = BLOCK_FACE_LEFT },
	{ .pos = VEC3(-0.5f, -0.5f,  0.5f), .uv = VEC2(1.0f, 0.0f), .face = BLOCK_FACE_LEFT },
	{ .pos = VEC3(-0.5f,  0.5f,  0.5f), .uv = VEC2(1.0f, 1.0f), .face = BLOCK_FACE_LEFT },
	{ .pos = VEC3(-0.5f,  0.5f, -0.5f), .uv = VEC2(0.0f, 1.0f), .face = BLOCK_FACE_LEFT },

	// Right
	{ .pos = VEC3( 0.5f, -0.5f,  0.5f), .uv = VEC2(0.0f, 0.0f), .face = BLOCK_FACE_RIGHT },
	{ .pos = VEC3( 0.5f, -0.5f, -0.5f), .uv = VEC2(1.0f, 0.0f), .face = BLOCK_FACE_RIGHT },
	{ .pos = VEC3( 0.5f,  0.5f, -0.5f), .uv = VEC2(1.0f, 1.0f), .face = BLOCK_FACE_RIGHT },
	{ .pos = VEC3( 0.5f,  0.5f,  0.5f), .uv = VEC2(0.0f, 1.0f), .face = BLOCK_FACE_RIGHT },
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

#endif // GEOMETRY_DATA_H
