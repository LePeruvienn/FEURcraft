#include "mesh.h"
#include "logger.h"
#include "mesh.h"
#include "debug.h"
#include "vertex_layout.h"

#include "glad/glad.h"
#include <stdlib.h>
#include <stddef.h>

Mesh* create_mesh(Geometry* g)
{
	Mesh* m = malloc(sizeof(struct Mesh));

	m->indices_amount = g->indices_amount;

	glGenVertexArrays(1, &m->VAO);
	glGenBuffers(1, &m->VBO);
	glGenBuffers(1, &m->EBO);

	glBindVertexArray(m->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

	vertex_layout layout = g->layout;
	
	setup_vao_attributes(layout);

	load_geometry_data(g);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return m;
}

Mesh* create_cube_mesh()
{
	Geometry* g = create_cube();
	Mesh* m = create_mesh(g);

	free_geometry(g);

	return m;
}

Mesh* create_sphere_mesh(float R, unsigned int lat_amount, unsigned int long_amount)
{
	Geometry* g = create_sphere(R, lat_amount, long_amount);
	Mesh* m = create_mesh(g);

	free_geometry(g);

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

void draw_mesh(Mesh* m, GLenum mode)
{
	if (m == NULL)
	{
		LOG_ERROR("Cannot draw a NULL mesh.");
		return;
	}

	GL_CALL(glDrawElements(
		mode,
		m->indices_amount,
		GL_UNSIGNED_INT,
		NULL
	));
}

void draw_mesh_instanced(Mesh* m, GLenum mode, unsigned int amount)
{
	if (m == NULL)
	{
		LOG_ERROR("Cannot draw a NULL mesh.");
		return;
	}

	GL_CALL(glDrawElementsInstanced(
		mode,
		m->indices_amount,
		GL_UNSIGNED_INT,
		NULL,
		amount
	));
}
