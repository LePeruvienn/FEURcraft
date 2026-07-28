#ifndef VERTEX_H
#define VERTEX_H

#include "vec3.h"
#include "vec2.h"

#include "block_face.h"

#include <stdint.h>

/**
 * \file vertex.h
 * \brief Fichier contenant les différent structure de vertex utilisable
 */

/**
 * \brief Type pour les vertex avec position et couleur,
 */
typedef struct Vertex Vertex;
typedef struct VertexUV VertexUV;
typedef struct VertexBlock VertexBlock;

struct Vertex
{
	Vec3 pos;
};

struct VertexUV
{
	Vec3 pos;
	Vec2 uv;
};

struct VertexBlock
{
	Vec3 pos;
	Vec2 uv;

	unsigned int layer_index;
};


#endif // VERTEX_H
