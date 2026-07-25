#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "mat4.h"
#include "mesh.h"

#include "logger.h"
#include "call_once.h"

static void log_matrices(Mat4 view, Mat4 model, Mat4 proj)
{
	unsigned int str_size = 256;
	char str_buf[str_size];

	mat4_to_str(view, str_buf, str_size);
	LOG("--- View Matrix ---");
	LOG("%s", str_buf);

	mat4_to_str(model, str_buf, str_size);
	LOG("--- Model Matrix (change) ---");
	LOG("%s", str_buf);

	mat4_to_str(proj, str_buf, str_size);
	LOG("--- Proj Matrix ---");
	LOG("%s", str_buf);
}

int main()
{
	Window* window = create_window(960, 680, "FEURcraft");

	Renderer renderer;
	renderer_init(&renderer, window);

	Shader* vert = shader_create("assets/shader/default.vert", SHADER_TYPE_VERT);
	Shader* frag = shader_create("assets/shader/default.frag", SHADER_TYPE_FRAG);

	shader_compile(vert);
	shader_compile(frag);

	ShaderProgram* program = shader_program_create();

	shader_program_attach(program, vert);
	shader_program_attach(program, frag);

	shader_program_link(program);

	Mesh* mesh = create_cube_mesh();

	float rotation = 0.f;

	while(!window_should_close(window))
	{
		window_pool_events();

		renderer_update_viewport(&renderer);

		renderer_clear();

		shader_program_use(program);

		float dt = window_get_delta_time(window);

		rotation += 0.5f * dt;

		Mat4 view = camera_compute_view(&renderer.camera);
		Mat4 model = mat4_mult(mat4_rotate_x(rotation), mat4_rotate_z(rotation));
		Mat4 proj = camera_compute_proj(&renderer.camera);

		CALL_ONCE(1, log_matrices(view, model, proj));

		shader_program_set_mat4(program, "uViewMatrix", view);
		shader_program_set_mat4(program, "uProjMatrix", proj);
		shader_program_set_mat4(program, "uModelMatrix", model);

		bind_mesh(mesh);

		draw_mesh(mesh, GL_LINE_STRIP);

		window_swap_buffers(window);
	}

	free_mesh(mesh);

	shader_program_free(program);
	
	shader_free(vert);
	shader_free(frag);

	free_window(window);
}
