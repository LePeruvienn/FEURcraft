#include "keyboard_key.h"

const char* keyboard_key_to_str(KeyboardKey key)
{
	switch(key)
	{
		case KEYBOARD_KEY_Z:      return "Z";
		case KEYBOARD_KEY_Q:      return "Q";
		case KEYBOARD_KEY_S:      return "S";
		case KEYBOARD_KEY_D:      return "D";
		
		case KEYBOARD_KEY_W:      return "W";
		case KEYBOARD_KEY_A:      return "A";
		
		case KEYBOARD_KEY_SPACE:  return "SPACE";
		case KEYBOARD_KEY_LSHIFT: return "LEFT SHIFT";
		case KEYBOARD_KEY_CTRL:   return "CTRL";
		
		case KEYBOARD_KEY_COUNT:  return "KEY_COUNT (INVALID)";
		default:                  return "UNKNOWN_KEY";
	}
}
