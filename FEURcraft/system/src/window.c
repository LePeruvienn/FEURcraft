#include "window.h"

#include "logger.h"
#include "error_checker.h"
#include "call_once.h"

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>
#include <threads.h>
#include <stdbool.h>

// IMPORTANT: MUST BE ENABLED WHEN DEBUGGING WITH RENDERDOC!
#define RENDER_DOC_DEBUG 1

#define _10e9 1000000000.0

Window* create_window(unsigned int width, unsigned int height, const char* title)
{
	static int is_glfw_init = false;

	CALL_ONCE(1,
		#if RENDER_DOC_DEBUG
			CALL_ONCE(2,
				glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11));
		#endif
		is_glfw_init = glfwInit()
	);

	CHECK_COND_RET(is_glfw_init != 0, "Failed to initialize GLFW", NULL);

	CALL_ONCE(3,
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// glfwWindowHint(GLFW_SAMPLES, 4); 
	);

	Window* w = malloc(sizeof(struct Window));

	if (w == NULL)
	{
		LOG_ERROR("Window malloc failed.");
		return NULL;
	}

	w->width = width;
	w->height = height;

	w->handle = glfwCreateWindow(width, height, title, NULL, NULL);

	if (w->handle == NULL)
	{
		LOG_ERROR("Failed to create GLFW window.");
		free(w);
		glfwTerminate();
		EXIT_PROGRAM(1);
	}

	glfwMakeContextCurrent(w->handle);
	glfwSetWindowUserPointer(w->handle, w);

	// On désactive le V-Sync
	glfwSwapInterval(0);

	return w;
}

void free_window(Window* w)
{
	CHECK_IS_NULL_RET(w, "Cannot free a NULL window", );

	if (w->handle)
	{
		glfwDestroyWindow(w->handle);
	}

	free(w);

	glfwTerminate();
}

bool window_should_close(Window* w) 
{
	CHECK_IS_NULL_RET(w, "Window is NULL, returning false.", false);

	return glfwWindowShouldClose(w->handle); 
}

void window_pool_events()
{
	glfwPollEvents();
}

void window_swap_buffers(Window* w)
{
	CHECK_IS_NULL_RET(w, "Cannot swap buffers of a NULL window.", );

	glfwSwapBuffers(w->handle);
}

void window_wait_events(double timeout)
{
	struct timespec ts;

	ts.tv_sec  = (time_t) timeout;
	ts.tv_nsec = (long) ((timeout - ts.tv_sec) * _10e9);

	thrd_sleep(&ts, NULL);
}

float window_get_time() 
{
	return (float) glfwGetTime(); 
}

void window_get_framebuffer_size(Window* w, int* width, int* height) 
{
	if (w && w->handle)
	{
		glfwGetFramebufferSize(w->handle, width, height);
	}
}

