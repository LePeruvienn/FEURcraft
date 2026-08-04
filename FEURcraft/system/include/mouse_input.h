#ifndef MOUSE_H
#define MOUSE_H

#include "window.h"

#include "vec2.h"

#include <stdbool.h>

typedef enum MouseButtonState MouseButtonState;

enum MouseButtonState
{
	MOUSE_BUTTON_PRESSED,
	MOUSE_BUTTON_DOWN,
	MOUSE_BUTTON_RELEASED,
	MOUSE_BUTTON_UP,
};

typedef enum MouseButton MouseButton;

enum MouseButton
{
	MOUSE_BUTTON_1 = 0,
	MOUSE_BUTTON_2,
	MOUSE_BUTTON_3,

	MOUSE_BUTTON_COUNT
};

typedef enum MouseCursorMode MouseCursorMode;

enum MouseCursorMode
{
	MOUSE_CURSOR_NORMAL,
	MOUSE_CURSOR_LOCK,
	MOUSE_CURSOR_HIDDEN,
};

typedef struct MouseInput MouseInput;

struct MouseInput
{
	Window* window;

	MouseCursorMode cursor_mode;

	MouseButtonState buttons[MOUSE_BUTTON_COUNT];

	Vec2 scroll_input;

	Vec2 old_screen_pos;
	Vec2 new_screen_pos;
	
	Vec2 screen_pos_diff;

	bool is_mouse_pos_init;
};

extern MouseButton MOUSE_BUTTON_LEFT;
extern MouseButton MOUSE_BUTTON_RIGHT;

void mouse_input_init(MouseInput* mouse, Window* window);

void mouse_input_update(MouseInput* mouse);

MouseButtonState mouse_input_get_button_state(MouseInput* mouse, MouseButton button);

MouseButtonState mouse_input_left_click_state(MouseInput* mouse);

MouseButtonState mouse_input_right_click_state(MouseInput* mouse);

void mouse_input_set_cursor_mode(MouseInput* mouse, MouseCursorMode cursor_mode);

#endif // MOUSE_H
