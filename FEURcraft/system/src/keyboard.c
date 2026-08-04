#include "keyboard.h"
#include "keyboard_key.h"

#include "error_checker.h"
#include "logger.h"

#include <GLFW/glfw3.h>

void keyboard_init(Keyboard* kb, Window* window)
{
	CHECK_IS_NULL_RET(kb, "Cannot init a NULL keyboard.", );
	CHECK_IS_NULL_RET(window, "Cannot init a keyboard with a NULL window.", );

	kb->window = window;

	for (unsigned int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
	{
		kb->keys[i] = KEY_UP;
	}
}

void keyboard_update(Keyboard* kb)
{
	CHECK_IS_NULL_RET(kb, "Cannot update a NULL keyboard.", );

	for (int key = 0; key < KEYBOARD_KEY_COUNT; ++key)
	{
		int glfw_key = -1;

		switch(key)
		{
			case KEYBOARD_KEY_Z: glfw_key = GLFW_KEY_Z;
				break;
			case KEYBOARD_KEY_Q: glfw_key = GLFW_KEY_Q;
				break;
			case KEYBOARD_KEY_S: glfw_key = GLFW_KEY_S;
				break;
			case KEYBOARD_KEY_D: glfw_key = GLFW_KEY_D;
				break;

			case KEYBOARD_KEY_W: glfw_key = GLFW_KEY_W;
				break;
			case KEYBOARD_KEY_A: glfw_key = GLFW_KEY_A;
				break;

			case KEYBOARD_KEY_SPACE: glfw_key = GLFW_KEY_SPACE;
				break;
			case KEYBOARD_KEY_LSHIFT: glfw_key = GLFW_KEY_LEFT_SHIFT;
				break;
			case KEYBOARD_KEY_CTRL: glfw_key = GLFW_KEY_LEFT_CONTROL;
				break;

			default:
				LOG_ERROR("Keyboad key is not supported");
				break;
		}

		if (glfw_key == -1)
		{
			LOG_ERROR("Failed to get keyboard key");
			continue;
		}

		int state = glfwGetKey(kb->window->handle, glfw_key);

		switch(state)
		{
			case GLFW_PRESS: kb->keys[key] = KEY_DOWN;
				break;

			default: kb->keys[key] = KEY_UP;
				break;
		}
	}
}

KeyState keyboard_get_key_state(Keyboard* kb, KeyboardKey key)
{
	CHECK_IS_NULL_RET(kb, "Cannot get key of a NULL keyboard.", KEY_UP);
	return kb->keys[key];
}

