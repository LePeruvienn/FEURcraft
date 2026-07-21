#include "window.h"
#include "logger.h"
#include "shader.h"
#include "shader_program.h"
#include "mesh.h"

int main()
{
	Window* window = create_window(960, 680, "FEURcraft");

	if (!gladLoadGL())
	{
		LOG_ERROR("Failed to initialize glad.");
		return 1;
	}

	Shader* vert = shader_create("assets/shader/default.vert", SHADER_TYPE_VERT);
	Shader* frag = shader_create("assets/shader/default.frag", SHADER_TYPE_FRAG);

	shader_compile(vert);
	shader_compile(frag);

	ShaderProgram* program = shader_program_create();

	shader_program_attach(program, vert);
	shader_program_attach(program, frag);

	shader_program_link(program);

	Mesh* mesh = create_cube_mesh();

	while(!window_should_close(window))
	{
		shader_program_use(program);
		bind_mesh(mesh);

		draw_mesh(mesh, GL_TRIANGLES);

		window_update_events(window);
	}

	free_mesh(mesh);

	shader_program_free(program);
	
	shader_free(vert);
	shader_free(frag);

	free_window(window);
}
