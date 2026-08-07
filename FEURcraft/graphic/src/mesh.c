#include "mesh.h"
#include "logger.h"
#include "mesh.h"
#include "gl_debug.h"
#include "vertex_layout.h"

#include "glad/glad.h"
#include <stdlib.h>
#include <stddef.h>

Mesh* create_mesh(Geometry* g)
{
	Mesh* m = malloc(sizeof(struct Mesh));

	m->indices_amount = g->indices->length;

	glGenVertexArrays(1, &m->VAO);
	glGenBuffers(1, &m->VBO);
	glGenBuffers(1, &m->EBO);

	glBindVertexArray(m->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

	VertexLayout* layout = &g->layout;
	
	vertex_layout_make_VAO(layout);

	geometry_load_to_gpu(g);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return m;
}

Mesh* create_cube_mesh()
{
	Geometry* g = geometry_create_cube();
	Mesh* m = create_mesh(g);

	geometry_free(g);

	return m;
}

Mesh* create_cube_uv_mesh()
{
	Geometry* g = geometry_create_cube_UV();
	Mesh* m = create_mesh(g);

	geometry_free(g);

	return m;
}

Mesh* create_block_mesh()
{
	Geometry* g = geometry_create_block();
	Mesh* m = create_mesh(g);

	geometry_free(g);

	return m;
}

Mesh* create_sphere_mesh(float R, unsigned int lat_amount, unsigned int long_amount)
{
	Geometry* g = geometry_create_sphere(R, lat_amount, long_amount);
	Mesh* m = create_mesh(g);

	geometry_free(g);

	return m;
}

void free_mesh(Mesh* m)
{
	if (m == NULL)
	{
		LOG_ERROR("Tried to free a NULL mesh");
		return;
	}

	glDeleteVertexArrays(1, &m->VAO);
	glDeleteBuffers(1, &m->VBO);
	glDeleteBuffers(1, &m->EBO);

	free(m);
}

void bind_mesh(Mesh* m)
{
	if (m == NULL)
	{
		LOG_ERROR("Trying to bind a null mesh");
	}

	GL_CALL(glBindVertexArray(m->VAO));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m->VBO));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO));
}

void unbind_mesh(Mesh* m)
{
	if (m == NULL)
	{
		LOG_ERROR("Trying to unbind a null mesh");
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static GLenum draw_mode_to_gl(DrawMode mode)
{
	switch(mode)
	{
		case DRAW_TRIANGLES:
			return GL_TRIANGLES;

		case DRAW_LINES:
			return GL_LINES;

		case DRAW_LINES_STRIP:
			return GL_LINE_LOOP;
	}

	LOG_ERROR("Failed to get GLenum from DrawMode. Return GL_TRIANGLES");

	return GL_TRIANGLES;
}

void draw_mesh(Mesh* m, DrawMode mode)
{
	if (m == NULL)
	{
		LOG_ERROR("Cannot draw a NULL mesh.");
		return;
	}

	GL_CALL(glDrawElements(
		draw_mode_to_gl(mode),
		m->indices_amount,
		GL_UNSIGNED_INT,
		NULL
	));
}

void draw_mesh_instanced(Mesh* m, DrawMode mode, unsigned int amount)
{
	if (m == NULL)
	{
		LOG_ERROR("Cannot draw a NULL mesh.");
		return;
	}

	GL_CALL(glDrawElementsInstanced(
		draw_mode_to_gl(mode),
		m->indices_amount,
		GL_UNSIGNED_INT,
		NULL,
		amount
	));
}
