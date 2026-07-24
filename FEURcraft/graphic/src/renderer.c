#include "renderer.h"
#include "camera.h"

#include "error_checker.h"

#include "glad/glad.h"

bool renderer_init(Renderer* renderer, Window* window)
{
	CHECK_IS_NULL_RET(renderer,
		"Cannot intialize a NULL renderer", false);

	CHECK_IS_NULL_RET(window,
		"Cannot intialize a renderer with a NULL window", false);

	static bool is_init  = false;
	static int is_glad_loaded = 0;

	if (is_init == false)
	{
		is_glad_loaded = gladLoadGL();
	}

	CHECK_COND_RET(is_glad_loaded == 0,
		"Error failed to load glad, can$not intialize renderer", false);

	renderer->window = window;

	camera_init_default(&renderer->camera, window);

	return true;
}

