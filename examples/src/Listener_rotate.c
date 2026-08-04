#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "mat4.h"
#include "mesh.h"
#include "image_array.h"
#include "texture_array.h"
#include "block_face.h"
#include "audio.h"

#include <math.h>

int main()
{
	Window* window = create_window(960, 680, "FEURcraft");

	Renderer renderer;
	renderer_init(&renderer, window);

	Shader* vert = shader_create("assets/shader/default_block.vert", SHADER_TYPE_VERT);
	Shader* frag = shader_create("assets/shader/default_block.frag", SHADER_TYPE_FRAG);

	shader_compile(vert);
	shader_compile(frag);

	ShaderProgram* program = shader_program_create();

	shader_program_attach(program, vert);
	shader_program_attach(program, frag);

	shader_program_link(program);

	Mesh* mesh = create_block_mesh();

	Image* block_images[BLOCK_FACE_COUNT];
	block_images[BLOCK_FACE_FRONT] = image_create_and_load("assets/textures/pumpkin_face_off.png");
	block_images[BLOCK_FACE_BACK ] = image_create_and_load("assets/textures/pumpkin_side.png");
	block_images[BLOCK_FACE_TOP  ] = image_create_and_load("assets/textures/pumpkin_top.png");
	block_images[BLOCK_FACE_BOT  ] = image_create_and_load("assets/textures/pumpkin_top.png");
	block_images[BLOCK_FACE_LEFT ] = image_create_and_load("assets/textures/pumpkin_side.png");
	block_images[BLOCK_FACE_RIGHT] = image_create_and_load("assets/textures/pumpkin_side.png");

	ImageArray* img_array = image_array_create(16, 16, 4);

	for (unsigned int i = 0; i < BLOCK_FACE_COUNT; ++i)
	{
		image_array_add_image(img_array, block_images[i]);
		image_free(block_images[i]);
		block_images[i] = NULL;
	}

	TextureArray* tex_array = texture_array_create_from_img_array(img_array);

	image_array_free(img_array);

	float rotation = 0.f;


	// AUDIO

	AudioConfig audioConf = AUDIO_INSTANTIATE();
	AudioListener audioLi = AUDIO_LISTENER_CREATE_WITH_POSITION(VEC3(0.f, 0.f, 5.f));
	AudioSource lel = AUDIO_SOURCE_CREATE("assets/audio/Waiting for transaction.wav");
	AudioEmitter audioEm = AUDIO_EMITTER_CREATE(lel);


	AUDIO_EMITTER_PLAY(audioEm);


	//
	float t;

	while(!window_should_close(window))
	{
		window_pool_events();

		renderer_update_viewport(&renderer);

		renderer_clear();

		shader_program_use(program);

		float dt = window_get_delta_time(window);



		// move camera
		renderer.camera.target = VEC3(cos(t*2), 0, sin(t*2) + 5);
		AUDIO_LISTENER_SET_ROTATION(audioLi, VEC3(cos(-t*2), 0, sin(-t*2)), VEC3(0.f, 1.f, 0.f));
		t += dt;




		rotation += 0.5f * dt;

		Mat4 view = camera_compute_view(&renderer.camera);
		Mat4 model = mat4_mult(mat4_rotate_x(rotation), mat4_rotate_z(rotation));
		Mat4 proj = camera_compute_proj(&renderer.camera);

		shader_program_set_mat4(program, "uViewMatrix", view);
		shader_program_set_mat4(program, "uProjMatrix", proj);
		shader_program_set_mat4(program, "uModelMatrix", model);

		unsigned int texture_unit = 0;
		texture_array_bind(tex_array, texture_unit);
		shader_program_set_texture_unit(program, "uTextureArray", texture_unit);

		bind_mesh(mesh);

		draw_mesh(mesh, DRAW_TRIANGLES);

		window_swap_buffers(window);
	}

	texture_array_free(tex_array);

	free_mesh(mesh);

	shader_program_free(program);
	
	shader_free(vert);
	shader_free(frag);

	free_window(window);
}
