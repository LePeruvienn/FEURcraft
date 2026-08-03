#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "window.h"
#include "keyboard_key.h"

typedef struct Keyboard Keyboard;

struct Keyboard
{
	Window* window;
	KeyState keys[KEYBOARD_KEY_COUNT];
};

void keyboard_init(Keyboard* kb, Window* window);

void keyboard_update(Keyboard* kb);

KeyState keyboard_get_key_state(Keyboard* kb, KeyboardKey key);

#endif // KEYBOARD_H
