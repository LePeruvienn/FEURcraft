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
	static int is_glfw_init = 0;

	if (is_glfw_init == 0) 
	{
		is_glfw_init = glfwInit();
	}	

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

	w->last_frame_time = (float) glfwGetTime();

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

float window_get_delta_time(Window* w)
{
	CHECK_IS_NULL_RET(w, "Cannot get delta time of NULL window.", 0.0f);

	float current_time = (float) glfwGetTime();
	float delta_time = current_time - w->last_frame_time;

	w->last_frame_time = current_time;

	return delta_time;
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

bool window_has_resized(Window* w)
{
	CHECK_IS_NULL_RET(w, "Cannot check resize of a NULL window", false);

	int current_width  = (int) w->width;
	int current_height = (int) w->height;

	glfwGetFramebufferSize(w->handle, &current_width, &current_height);

	if (current_width  == (int) w->width &&
	    current_height == (int) w->height)
	{
		return false;
	}

	CHECK_COND_RET(current_width > 0 && current_height > 0,
		"Framebuffer size is less or equal than zero. returning", false)

	w->width  = (unsigned int) current_width;
	w->height = (unsigned int) current_height;

	return true;
}

