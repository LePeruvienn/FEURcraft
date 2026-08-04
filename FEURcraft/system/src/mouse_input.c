#include "mouse_input.h"

#include "vec2.h"

#include "error_checker.h"
#include "logger.h"

#include <GLFW/glfw3.h>

#include <stdbool.h>

MouseButton MOUSE_BUTTON_LEFT  = MOUSE_BUTTON_1;
MouseButton MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2;

#define CHECK_MOUSE_INPUT_OK(mouse_ptr, ret) CHECK_IS_NULL_RET((mouse_ptr), "MouseInput is NULL", ret); \
                                             CHECK_IS_NULL_RET((mouse_ptr)->window, "MouseInput Window is NULL", ret);


static Vec2 global_scroll = {{{ 0.f, 0.f }}};

static void glfw_scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	(void) window;

	global_scroll.x = x_offset;
	global_scroll.y = y_offset;
}

void mouse_input_init(MouseInput* mouse, Window* window)
{
	CHECK_IS_NULL_RET(mouse, "Cannot init a NULL MouseInput", );
	CHECK_IS_NULL_RET(window, "Cannot init a MouseInput with a NULL Window", );

	mouse->window = window;

	glfwSetScrollCallback(window->handle, glfw_scroll_callback);

	mouse->scroll_input = VEC2_ZERO;
	mouse->old_screen_pos = VEC2_ZERO;
	mouse->new_screen_pos = VEC2_ZERO;
	mouse->screen_pos_diff = VEC2_ZERO;

	mouse->is_mouse_pos_init = false;
}

static unsigned int glfw_get_mouse_button_id(MouseButton button)
{
	switch(button)
	{
		case MOUSE_BUTTON_1:
			return GLFW_MOUSE_BUTTON_1;

		case MOUSE_BUTTON_2:
			return GLFW_MOUSE_BUTTON_2;

		case MOUSE_BUTTON_3:
			return GLFW_MOUSE_BUTTON_3;

		default:
			LOG_ERROR("Failed to get GLFW mouse button.");
			break;
	}

	return 0;
}

void mouse_input_update(MouseInput* mouse)
{
	CHECK_MOUSE_INPUT_OK(mouse, );

	GLFWwindow* handle = mouse->window->handle;
	
	mouse->old_screen_pos = mouse->new_screen_pos;

	double x_pos, y_pos;
	glfwGetCursorPos(handle, &x_pos, &y_pos);

	mouse->new_screen_pos = VEC2(x_pos, y_pos);

	if (mouse->is_mouse_pos_init == false)
	{
		mouse->old_screen_pos = mouse->new_screen_pos;
		mouse->is_mouse_pos_init = true;
	}

	mouse->screen_pos_diff = vec2_sub(mouse->new_screen_pos,
	                                  mouse->old_screen_pos);

	mouse->scroll_input = global_scroll;

	for (unsigned int i = 0; i < MOUSE_BUTTON_COUNT; ++i)
	{
		unsigned int glfw_button =  glfw_get_mouse_button_id(i);

		int state = glfwGetMouseButton(handle, glfw_button);

		if(state == GLFW_PRESS)
		{
			mouse->buttons[i] = MOUSE_BUTTON_DOWN;
		}
		else
		{
			mouse->buttons[i] = MOUSE_BUTTON_UP;
		}
	}
}

MouseButtonState mouse_input_get_button_state(MouseInput* mouse, MouseButton button)
{
	CHECK_MOUSE_INPUT_OK(mouse, MOUSE_BUTTON_UP);

	return mouse->buttons[button];
}

MouseButtonState mouse_input_left_click_state(MouseInput* mouse)
{
	return mouse_input_get_button_state(mouse, MOUSE_BUTTON_LEFT);
}

MouseButtonState mouse_input_right_click_state(MouseInput* mouse)
{
	return mouse_input_get_button_state(mouse, MOUSE_BUTTON_RIGHT);
}

static unsigned int glfw_get_cursor_mode(MouseCursorMode cursor_mode)
{
	switch(cursor_mode)
	{
		case MOUSE_CURSOR_NORMAL:
			return GLFW_CURSOR_NORMAL;

		case MOUSE_CURSOR_LOCK:
			return GLFW_CURSOR_DISABLED;

		case MOUSE_CURSOR_HIDDEN:
			return GLFW_CURSOR_HIDDEN;

		default:
			LOG_ERROR("Failed to get glfw MouseCursorMode.");
	}

	return 0;
}

void mouse_input_set_cursor_mode(MouseInput* mouse, MouseCursorMode cursor_mode)
{
	CHECK_MOUSE_INPUT_OK(mouse, );

	unsigned int glfw_cursor_mode = glfw_get_cursor_mode(cursor_mode);
	glfwSetInputMode(mouse->window->handle, GLFW_CURSOR, glfw_cursor_mode);
}
