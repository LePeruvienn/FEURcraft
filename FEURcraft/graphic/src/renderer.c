#include "renderer.h"
#include "camera.h"

#include "error_checker.h"
#include "call_once.h"

#include "glad/glad.h"

static void set_default_gl_params()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

bool renderer_init(Renderer* renderer, Window* window)
{
	CHECK_IS_NULL_RET(renderer,
		"Cannot intialize a NULL renderer", false);

	CHECK_IS_NULL_RET(window,
		"Cannot intialize a renderer with a NULL window", false);

	static int is_glad_loaded = 0;

	CALL_ONCE(1, is_glad_loaded = gladLoadGL());

	CHECK_COND_RET(is_glad_loaded != 0,
		"Error failed to load glad, cannot intialize renderer", false);

	CALL_ONCE(2, set_default_gl_params());

	renderer->window = window;

	camera_init_default(&renderer->camera, window);

	return true;
}

void renderer_clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
