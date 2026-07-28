#include "geometry.h"
#include "geometry_data.h"
#include "vertex.h"
#include "vertex_layout.h"
#include "logger.h"
#include "gl_debug.h"
#include "error_checker.h"

#include "ptr_helper.h"

#include "array_list.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

Geometry* geometry_create_empty(VertexLayout layout)
{
	ArrayList* vertices = array_list_create(layout.vertex_byte_size, 16);
	ArrayList* indices = array_list_create(sizeof(unsigned int), 16);
	
	if (vertices == NULL || indices == NULL)
	{
		LOG_ERROR("Failed to create Geometry vertices or indices ArrayList.");

		FREE_PTR_NOT_NULL(vertices, array_list_free);
		FREE_PTR_NOT_NULL(indices, array_list_free);

		return NULL;
	}

	Geometry* geometry = malloc(sizeof(struct Geometry));

	geometry->vertices = vertices;
	geometry->indices = indices;

	geometry->layout = layout;

	return geometry;
}

Geometry* geometry_create(const void* vertices_buffer, size_t vertices_amount,
                          const unsigned int* indices_buffer, size_t indices_amount,
                          VertexLayout layout)
{
	CHECK_IS_NULL_RET(vertices_buffer, "Cannot create a Geometry with NULL vertices.", NULL);
	CHECK_IS_NULL_RET(indices_buffer, "Cannot create a Geometry with NULL indices.", NULL);

	CHECK_COND_RET(vertices_amount > 0,
		"Cannot create a Geometry with 0 vertices amount.", NULL);

	CHECK_COND_RET(indices_amount >= vertices_amount,
		"Cannot create a Geometry with less indices than vertices", NULL);

	ArrayList* vertices = array_list_create(layout.vertex_byte_size, vertices_amount);
	ArrayList* indices = array_list_create(sizeof(unsigned int), indices_amount);

	CHECK_IS_NULL_RET(vertices,
		"Cannot create Geometry failed to create vertices ArrayList.", NULL);

	CHECK_IS_NULL_RET(indices,
		"Cannot create Geometry failed to create indices ArrayList.", NULL);

	array_list_push_buffer(vertices, vertices_buffer, vertices_amount);

	if (vertices->count != vertices_amount)
	{
		LOG_ERROR("Failed to add vertices to vertices array.");
		array_list_free(vertices);
		return NULL;
	}

	array_list_push_buffer(indices, indices_buffer, indices_amount);

	if (indices->count != indices_amount)
	{
		LOG_ERROR("Failed to add indices to indices array.");
		array_list_free(vertices);
		array_list_free(indices);
		return NULL;
	}

	Geometry* geometry = malloc(sizeof(struct Geometry));

	geometry->vertices = vertices;
	geometry->indices = indices;
	geometry->layout = layout;

	return geometry;
}

Geometry* geometry_create_cube()
{
	VertexLayout layout;
	vertex_layout_init_default(&layout);

	return geometry_create(CUBE_VERTICES, CUBE_VERTICES_AMOUNT,
	                       CUBE_INDICES, CUBE_INDICES_AMOUNT, layout);
}

Geometry* geometry_create_cube_UV()
{
	VertexLayout layout;
	vertex_layout_init_default_UV(&layout);

	return geometry_create(CUBE_UV_VERTICES, CUBE_UV_VERTICES_AMOUNT,
	                       CUBE_UV_INDICES, CUBE_UV_INDICES_AMOUNT, layout);
}

Geometry* geometry_create_block()
{
	VertexLayout layout;
	vertex_layout_init_default_block(&layout);

	return geometry_create(BLOCK_VERTICES, BLOCK_VERTICES_AMOUNT,
	                       BLOCK_INDICES, BLOCK_INDICES_AMOUNT, layout);
}

Geometry* geometry_create_sphere(float R, unsigned int lat_amount, unsigned int long_amount)
{
	if (R <= 0.f)
	{
		LOG_ERROR("Sphere radius cannot equal to zero.");
		return NULL;
	}

	unsigned int vertices_amount = (lat_amount + 1) * (long_amount + 1);
	unsigned int indices_amount = lat_amount * long_amount * 6;

	size_t vertices_size = sizeof(Vertex) * vertices_amount;
	
	Vertex* vertices = malloc(vertices_size);
	unsigned int* indices = malloc(sizeof(unsigned int) * indices_amount);

	float step_lat = M_PI / lat_amount;
	float step_long = (2.f * M_PI) / long_amount;

	unsigned int vertex_i = 0;

	for (unsigned int i = 0; i <= lat_amount; ++i)
	{
		float lat_angle = i * step_lat;

		for (unsigned int j = 0; j <= long_amount; ++j)
		{
			float long_angle = j * step_long;

			float x = R * sinf(lat_angle) * cosf(long_angle);
			float y = R * sinf(lat_angle) * sinf(long_angle);
			float z = R * cosf(lat_angle);

			vertices[vertex_i].pos.x = x;
			vertices[vertex_i].pos.y = y;
			vertices[vertex_i].pos.z = z;

			++vertex_i;
		}
	}

	unsigned int indice_i = 0;

	for (unsigned int i = 0; i < lat_amount; ++i)
	{
		for (unsigned int j = 0; j < long_amount; ++j)
		{
			unsigned int k1 = i * (long_amount + 1) + j;
			unsigned int k2 = k1 + long_amount + 1;

			indices[indice_i++] = k1;
			indices[indice_i++] = k2;
			indices[indice_i++] = k1 + 1;

			indices[indice_i++] = k1 + 1;
			indices[indice_i++] = k2;
			indices[indice_i++] = k2 + 1;
		}
	}

	VertexLayout layout;
	vertex_layout_init_default(&layout);

	return geometry_create(vertices, vertices_amount,
	                       indices, indices_amount, layout);
}

void geometry_add_array(Geometry* g, const ArrayList* vertices, const ArrayList* indices)
{
	CHECK_IS_NULL_RET(g, "Cannot add buffer to NULL Geometry.", );
	CHECK_IS_NULL_RET(vertices, "Cannot add NULL vertices ArrayList to Geometry.", );
	CHECK_IS_NULL_RET(indices, "Cannot add NULL indices ArrayList to Geometry.", );

	size_t old_indices_count = g->indices->count;

	array_list_push_array(g->indices, indices);

	size_t new_indices_count = g->indices->count;

	// Applying indices offset to new indices
	for (size_t i = old_indices_count; i < new_indices_count; ++i)
	{
		unsigned int* indice = array_list_get(g->indices, i);

		if (indice == NULL)
		{
			LOG_ERROR("Failed to get indices from Geometry indices buffer.");
			continue;
		}

		*indice += g->vertices->count;
	}

	array_list_push_array(g->vertices, vertices);
}

void geometry_add_buffer(Geometry* g, const void* vertices_buffer, size_t vertices_amount,
                         const unsigned int* indices_buffer, size_t indices_amount)
{
	CHECK_IS_NULL_RET(g, "Cannot add buffer to NULL Geometry.", );

	CHECK_IS_NULL_RET(vertices_buffer,
		"Cannot add NULL vertices buffer to Geometry.", );

	CHECK_IS_NULL_RET(indices_buffer,
		"Cannot add NULL indices buffer to Geometry.", );

	size_t old_indices_count = g->indices->count;

	array_list_push_buffer(g->indices, indices_buffer, indices_amount);

	size_t new_indices_count = g->indices->count;

	// Applying indices offset to new indices
	for (size_t i = old_indices_count; i < new_indices_count; ++i)
	{
		unsigned int* indice = array_list_get(g->indices, i);

		if (indice == NULL)
		{
			LOG_ERROR("Failed to get indices from Geometry indices buffer.");
			continue;
		}

		*indice += g->vertices->count;
	}

	array_list_push_buffer(g->vertices, vertices_buffer, vertices_amount);
}

void geometry_load_to_gpu(Geometry* g)
{
	LOG_INFO("Loaded a geometry to GPU of %zu vertices and %zu indices", g->vertices->count, g->indices->count);

	GL_CALL(glBufferData(GL_ARRAY_BUFFER,
	             g->vertices->item_size * g->vertices->count,
	             g->vertices->data,
	             GL_STATIC_DRAW));

	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             sizeof(unsigned int) * g->indices->count,
	             g->indices->data,
	             GL_STATIC_DRAW));
}

void geometry_free(Geometry* g)
{
	array_list_free(g->vertices);
	array_list_free(g->indices);
	free(g);
}
