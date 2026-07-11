#include "mesh.h"
#include "vertex.h"
#include "vertex_layout.h"
#include "logger.h"
#include "debug.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#define M_PI 3.14159265358979323846

#define CUBE_VERTICES_AMOUNT 8
#define CUBE_INDICES_AMOUNT 36

struct mesh
{
	void* vertices; // Peut contenir différent type de vertex
	size_t vertices_size;
	unsigned int vertices_amount;

	unsigned int* indices;
	unsigned int indices_amount;

	vertex_layout layout; // doit être corda avec les type de vertex dans le buffer
};

mesh create_cube()
{
	mesh m = malloc(sizeof(struct mesh));

	m->vertices = NULL;
	m->vertices_size = sizeof(vertex) * CUBE_VERTICES_AMOUNT;
	m->vertices_amount = CUBE_VERTICES_AMOUNT;

	m->indices = NULL;
	m->indices_amount = CUBE_INDICES_AMOUNT;

	vertex vertices[CUBE_VERTICES_AMOUNT] = {

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

	unsigned int indices[CUBE_INDICES_AMOUNT] = {

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

	m->vertices = malloc(m->vertices_size);
	memcpy(m->vertices, vertices, m->vertices_size);

	m->indices = malloc(sizeof(unsigned int) * m->indices_amount);
	memcpy(m->indices, indices, sizeof(unsigned int) * m->indices_amount);	

	m->layout = create_vertex_layout();

	return m;
}

mesh create_sphere(float R, unsigned int lat_amount, unsigned int long_amount)
{
	if (R <= 0.f)
	{
		LOG_ERROR("Sphere radius cannot equal to zero.");
		return NULL;
	}

	unsigned int vertices_amount = (lat_amount + 1) * (long_amount + 1);
	unsigned int indices_amount = lat_amount * long_amount * 6;

	size_t vertices_size = sizeof(vertex) * vertices_amount;
	
	vertex* vertices = malloc(vertices_size);
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

	mesh m = malloc(sizeof(struct mesh));

	m->vertices = vertices;
	m->vertices_size = vertices_size;
	m->vertices_amount = vertices_amount;

	m->indices = indices;
	m->indices_amount = indices_amount;

	m->layout = create_vertex_layout();

	return m;
}

mesh create_line(vertex* vertices, unsigned int size)
{
	mesh m = malloc(sizeof(struct mesh));

	m->vertices = NULL;
	m->vertices_size = sizeof(vertex) * size;
	m->vertices_amount = size;

	m->indices = NULL;
	m->indices_amount = size;

	m->vertices = malloc(m->vertices_size);
	m->indices = malloc(sizeof(vertex) * m->indices_amount);

	memcpy(m->vertices, vertices, size);

	for (unsigned int i = 0; i < size; i++)
	{
		m->indices[i] = i;
	}

	m->layout = create_vertex_layout();

	return m;
}

void load_mesh_data(mesh m)
{
	LOG_INFO("Loaded a mesh to GPU of %u vertices and %u indices", m->vertices_amount, m->indices_amount);

	GL_CALL(glBufferData(GL_ARRAY_BUFFER,
	             m->vertices_size,
	             m->vertices,
	             GL_STATIC_DRAW));

	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             sizeof(unsigned int) * m->indices_amount,
	             m->indices,
	             GL_STATIC_DRAW));
}

void free_mesh(mesh m)
{
	free_vertex_layout(m->layout);
	free(m->vertices);
	free(m->indices);
	free(m);
}

unsigned int get_mesh_indices_amount(mesh m)
{
	return m->indices_amount;
}

vertex_layout get_mesh_vertex_layout(mesh m)
{
	return m->layout;
}
