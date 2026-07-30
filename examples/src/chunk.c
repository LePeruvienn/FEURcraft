#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "mesh.h"
#include "image_array.h"
#include "texture_array.h"
#include "chunk_geometry.h"

#include "mat4.h"

#include "block.h"
#include "block_face.h"
#include "chunk.h"

#include "error_checker.h"

static Mesh* create_chunk_mesh(const Chunk* chunk)
{
	Geometry* chunk_geometry = chunk_geometry_create(chunk);

	CHECK_IS_NULL_RET(chunk_geometry, "Failed to create Chunk geometry", NULL);

	Mesh* chunk_mesh = create_mesh(chunk_geometry);

	geometry_free(chunk_geometry);
	
	return chunk_mesh;
}

static TextureArray* create_block_texture_array()
{
	#define BLOCK_TEXTURE_COUNT (BLOCK_COUNT * BLOCK_FACE_COUNT)

	Image* block_images[BLOCK_TEXTURE_COUNT];

	for(unsigned int i = 0; i < BLOCK_TEXTURE_COUNT; i += BLOCK_FACE_COUNT)
	{
		block_images[i + BLOCK_FACE_FRONT] = image_create_and_load("assets/textures/pumpkin_face_off.png");
		block_images[i + BLOCK_FACE_BACK ] = image_create_and_load("assets/textures/pumpkin_side.png");
		block_images[i + BLOCK_FACE_TOP  ] = image_create_and_load("assets/textures/pumpkin_top.png");
		block_images[i + BLOCK_FACE_BOT  ] = image_create_and_load("assets/textures/pumpkin_top.png");
		block_images[i + BLOCK_FACE_LEFT ] = image_create_and_load("assets/textures/pumpkin_side.png");
		block_images[i + BLOCK_FACE_RIGHT] = image_create_and_load("assets/textures/pumpkin_side.png");
	}

	ImageArray* img_array = image_array_create(16, 16, 4);

	for (unsigned int i = 0; i < BLOCK_TEXTURE_COUNT ; ++i)
	{
		image_array_add_image(img_array, block_images[i]);
		image_free(block_images[i]);
		block_images[i] = NULL;
	}

	TextureArray* tex_array = texture_array_create_from_img_array(img_array);

	image_array_free(img_array);

	return tex_array;
}

int main()
{
	Window* window = create_window(960, 680, "FEURcraft");

	Renderer renderer;
	renderer_init(&renderer, window);

	Shader* vert = shader_create("assets/shader/default_block.vert", SHADER_TYPE_VERT);
	Shader* frag = shader_create("assets/shader/default_block.frag", SHADER_TYPE_FRAG);

	Shader* frag_debug = shader_create("assets/shader/red.frag", SHADER_TYPE_FRAG);

	shader_compile(vert);
	shader_compile(frag);
	shader_compile(frag_debug);

	ShaderProgram* program = shader_program_create();
	ShaderProgram* program_debug = shader_program_create();

	shader_program_attach(program, vert);
	shader_program_attach(program, frag);

	shader_program_attach(program_debug, vert);
	shader_program_attach(program_debug, frag_debug);

	shader_program_link(program);
	shader_program_link(program_debug);

	Chunk chunk = CHUNK_EMPTY;

	chunk_fill(&chunk, BLOCK_DIRT, (CHUNK_HEIGHT / 2) - 5);
	Mesh* mesh_world = create_chunk_mesh(&chunk);

	chunk_fill_all(&chunk, BLOCK_DIRT);
	Mesh* mesh_debug = create_chunk_mesh(&chunk);

	TextureArray* tex_array = create_block_texture_array();

	float rotation = 0.f;

	float camera_dist_max = - CHUNK_LENGTH;
	float camera_dist_min = - (CHUNK_LENGTH  * 4);
	float camera_sign = -1.f;

	while(!window_should_close(window))
	{
		window_pool_events();

		renderer_update_viewport(&renderer);

		renderer_clear();

		float dt = window_get_delta_time(window);

		// Move camera

		if ((camera_sign > 0 && camera_dist_max < renderer.camera.pos.z) ||
		    (camera_sign < 0 && camera_dist_min > renderer.camera.pos.z))
		{
			camera_sign *= -1;
		}

		renderer.camera.pos.z += camera_sign * CHUNK_LENGTH * dt;


		// Draw Chunk

		shader_program_use(program);

		rotation += 0.5f * dt;

		// Center chunk
		Vec3 center = VEC3(
			- (CHUNK_LENGTH / 2),
			- (CHUNK_HEIGHT / 2),
			- (CHUNK_LENGTH / 2)
		);

		Mat4 view = camera_compute_view(&renderer.camera);
		Mat4 model = mat4_mult(mat4_rotate_y(rotation), mat4_translate(center));
		Mat4 proj = camera_compute_proj(&renderer.camera);

		shader_program_set_mat4(program, "uViewMatrix", view);
		shader_program_set_mat4(program, "uProjMatrix", proj);
		shader_program_set_mat4(program, "uModelMatrix", model);

		unsigned int texture_unit = 0;
		texture_array_bind(tex_array, texture_unit);
		shader_program_set_texture_unit(program, "uTextureArray", texture_unit);

		bind_mesh(mesh_world);
		draw_mesh(mesh_world, GL_TRIANGLES);

		// Draw debug lines

		shader_program_use(program_debug);

		shader_program_set_mat4(program_debug, "uViewMatrix", view);
		shader_program_set_mat4(program_debug, "uProjMatrix", proj);
		shader_program_set_mat4(program_debug, "uModelMatrix", model);

		bind_mesh(mesh_debug);
		draw_mesh(mesh_debug, GL_LINES);

		window_swap_buffers(window);
	}

	texture_array_free(tex_array);

	free_mesh(mesh_world);
	free_mesh(mesh_debug);

	shader_program_free(program);
	
	shader_free(vert);
	shader_free(frag);

	free_window(window);
}
