#ifndef KEYBOARD_KEY_H
#define KEYBOARD_KEY_H

typedef enum KeyState KeyState;

enum KeyState
{
	KEY_PRESSED,
	KEY_DOWN,
	KEY_RELEASE,
	KEY_UP
};

typedef enum KeyboardKey KeyboardKey;

enum KeyboardKey
{
	KEYBOARD_KEY_UNKNOWN = -1,

	KEYBOARD_KEY_Z = 0,
	KEYBOARD_KEY_Q,
	KEYBOARD_KEY_S,
	KEYBOARD_KEY_D,

	KEYBOARD_KEY_W,
	KEYBOARD_KEY_A,

	KEYBOARD_KEY_SPACE,
	KEYBOARD_KEY_LSHIFT,
	KEYBOARD_KEY_CTRL,

	KEYBOARD_KEY_COUNT
};

const char* keyboard_key_to_str(KeyboardKey key);

#endif // KEYBOARD_KEY_H
