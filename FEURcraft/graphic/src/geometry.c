#include "geometry.h"
#include "logger.h"
#include "mesh.h"
#include "debug.h"
#include "vertex_layout.h"

#include "glad/glad.h"
#include <stdlib.h>
#include <stddef.h>

struct geometry
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLenum type;
	unsigned int indices_amount;
};

geometry create_geometry(mesh m)
{
	geometry g = malloc(sizeof(struct geometry));

	g->indices_amount = get_mesh_indices_amount(m);

	glGenVertexArrays(1, &g->VAO);
	glGenBuffers(1, &g->VBO);
	glGenBuffers(1, &g->EBO);

	glBindVertexArray(g->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, g->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->EBO);

	vertex_layout layout = get_mesh_vertex_layout(m);
	
	setup_vao_attributes(layout);

	load_mesh_data(m);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return g;
}

geometry create_cube_geometry()
{
	mesh m = create_cube();
	geometry g = create_geometry(m);

	free_mesh(m);

	return g;
}

geometry create_sphere_geometry(float R, unsigned int lat_amount, unsigned int long_amount)
{
	mesh m = create_sphere(R, lat_amount, long_amount);
	geometry g = create_geometry(m);

	free_mesh(m);

	return g;
}

void free_geometry(geometry g)
{
	if (g == NULL)
	{
		LOG_ERROR("Tried to free a NULL geometry");
		return;
	}

	glDeleteVertexArrays(1, &g->VAO);
	glDeleteBuffers(1, &g->VBO);
	glDeleteBuffers(1, &g->EBO);

	free(g);
}

void bind_geometry(geometry g)
{
	if (g == NULL)
	{
		LOG_ERROR("Trying to bind a null geometry");
	}

	GL_CALL(glBindVertexArray(g->VAO));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, g->VBO));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->EBO));
}

void unbind_geometry(geometry g)
{
	if (g == NULL)
	{
		LOG_ERROR("Trying to unbind a null geometry");
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void draw_geometry(geometry g, GLenum mode)
{
	if (g == NULL)
	{
		LOG_ERROR("Cannot draw a NULL geometry.");
		return;
	}

	GL_CALL(glDrawElements(
		mode,
		g->indices_amount,
		GL_UNSIGNED_INT,
		NULL
	));
}

void draw_geometry_instanced(geometry g, GLenum mode, unsigned int amount)
{
	if (g == NULL)
	{
		LOG_ERROR("Cannot draw a NULL geometry.");
		return;
	}

	GL_CALL(glDrawElementsInstanced(
		mode,
		g->indices_amount,
		GL_UNSIGNED_INT,
		NULL,
		amount
	));
}
