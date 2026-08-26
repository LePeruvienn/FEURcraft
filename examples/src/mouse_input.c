#include "window.h"
#include "renderer.h"
#include "mouse_input.h"

#include "vec2.h"

#include "logger.h"

int main()
{
	Window* window = create_window(960, 800, "Mouse input test");

	Renderer renderer;
	renderer_init(&renderer, window);

	MouseInput mouse;

	mouse_input_init(&mouse, window);

	LOG("Try moving the mouse !");

	MouseButtonState old_left_click = mouse_input_left_click_state(&mouse);
	MouseButtonState old_right_click = mouse_input_right_click_state(&mouse);

	Vec2 old_screen_pos_diff = mouse.screen_pos_diff;
	Vec2 old_scroll_input = mouse.scroll_input;

	while(!window_should_close(window))
	{
		window_pool_events();

		mouse_input_update(&mouse);

		MouseButtonState left_click  = mouse_input_left_click_state(&mouse);
		MouseButtonState right_click = mouse_input_right_click_state(&mouse);

		bool mouse_clicked = (old_left_click != left_click || old_right_click != right_click);

		bool mouse_moved = !vec2_equal(old_screen_pos_diff, mouse.screen_pos_diff);
		bool mouse_scrolled = !vec2_equal(old_scroll_input, mouse.scroll_input);

		if(mouse_clicked || mouse_moved || mouse_scrolled)
		{
			LOG("Mouse: move=(%.1f, %.1f) scroll=(%.1f, %.1f) Left=\"%s\" Right=\"%s\"",
				mouse.screen_pos_diff.x,
				mouse.screen_pos_diff.y,
				mouse.scroll_input.x,
				mouse.scroll_input.y,
				mouse_button_state_to_str(left_click),
				mouse_button_state_to_str(right_click));
		}

		old_left_click = left_click;
		old_right_click = right_click;

		old_screen_pos_diff = mouse.screen_pos_diff;
		old_scroll_input = mouse.scroll_input;

		renderer_update_viewport(&renderer);
		renderer_clear();

		window_swap_buffers(window);
	}

	free_window(window);
}
