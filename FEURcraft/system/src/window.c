#include "window.h"

#include "logger.h"

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>
#include <threads.h>

#define _10e9 1000000000.0

Window* create_window(unsigned int width, unsigned int height, const char* title)
{
	if (!glfwInit())
	{
		LOG_ERROR("Failed to initialize GLFW.");
		EXIT_PROGRAM(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); 

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
	if (w == NULL)
	{
		return;
	}

	if (w->handle)
	{
		glfwDestroyWindow(w->handle);
	}

	free(w);

	glfwTerminate();
}

bool window_should_close(Window* w) 
{ 
	return glfwWindowShouldClose(w->handle); 
}

void window_update_events(Window* w) 
{ 
	glfwSwapBuffers(w->handle); 
	glfwPollEvents(); 
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

