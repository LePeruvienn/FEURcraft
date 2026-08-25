#include "window.h"
#include "renderer.h"
#include "keyboard.h"
#include "keyboard_key.h"

#include "logger.h"

int main()
{
	Window* window = create_window(960, 800, "Keyboard test");

	Renderer renderer;
	renderer_init(&renderer, window);

	Keyboard keyboard;
	keyboard_init(&keyboard, window);

	LOG("Try pressing some keyboard keys !");

	KeyboardKey last_key = KEYBOARD_KEY_UNKNOWN;

	while(!window_should_close(window))
	{
		window_pool_events();

		renderer_update_viewport(&renderer);
		renderer_clear();

		keyboard_update(&keyboard);

		for (int key = 0; key < KEYBOARD_KEY_COUNT; ++key)
		{
			KeyState state = keyboard_get_key_state(&keyboard, key);

			if (state == KEY_DOWN && last_key != key)
			{
				const char* key_str = keyboard_key_to_str(key);
				LOG("You pressed the key : %s", key_str);

				last_key = key;
			}
		}

		window_swap_buffers(window);
	}

	free_window(window);
}
