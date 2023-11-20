#include <stddef.h>

#include "timer.h"
#include "gameboard.h"
#include "renderer.h"

void on_key_pressed(key_t const key, action_t const action) {
	int dx = 0;
	int dy = 0;

	switch (key) {
	case key_down: dy = -1; break;
	case key_left: dx = -1; break;
	case key_right: dx = 1; break;
	case key_up: dy = 1; break;
	}

	if (action == action_press || action == action_release) {
		try_move(dx, dy);
	}
}

void on_timer_elapsed(void) {
	on_key_pressed(key_down, action_press);
}

int main() {
	renderer_init(GB_ROWS, GB_COLS, on_key_pressed);
	timer_init(on_timer_elapsed);

	while(renderer_open()) {
		renderer_begin_frame();

		timer_test();

		block current = get_current_block();
		renderer_render(current.pos, current.color);

		renderer_end_frame();
	}

	renderer_shutdown();
}
