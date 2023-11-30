#include <stddef.h>
#include <stdbool.h>

#include "timer.h"
#include "gameboard.h"
#include "renderer.h"
#include "types.h"

void on_current_block_collided(void);

void gameloop(key_t const key, action_t const action) {
	int dx = 0;
	int dy = 0;

	switch (key) {
		case key_down: dy = -1; break;
		case key_left: dx = -1; break;
		case key_right: dx = 1; break;
	}

	if (action == action_press || action == action_repeat) {
		bool move_successful = try_move_current(dx, dy);
		if (!move_successful && dx == 0) {
			on_current_block_collided();
		}
	}
}

void on_current_block_collided(void) {
	// fix block at current position and spawn new block
	block current = get_current_block();
	set_block_at(current.pos, current);

	// todo clear full rows (bottom up) (nested loops)
	// for block in fixedblocks (bottom up)
	//		while (try_move()) #move_down

	spawn_new_block();
}

void render_blocks(void) {
	block current = get_current_block();
	renderer_render(current.pos, current.color);

	for (int y = 0; y < GB_ROWS; y++) {
		for (int x = 0; x < GB_COLS; x++) {
			position pos = { x, y };
			block b = get_block_at(pos);
			if (!is_empty_block(b))
			{
				renderer_render(b.pos, b.color);
			}
		}
	}
}

void on_key_pressed(key_t const key, action_t const action) {
	gameloop(key, action);
}

void on_timer_elapsed(void) {
	on_key_pressed(key_down, action_press);
}

int main() {
	// TODO Repo in ue05-saalmi umziehen!!!!

	init_gameboard();
	renderer_init(GB_ROWS, GB_COLS, on_key_pressed);
	timer_init(on_timer_elapsed);

	spawn_new_block();

	while(renderer_open()) {
		renderer_begin_frame();

		timer_test();
	
		render_blocks();

		renderer_end_frame();
	}

	renderer_shutdown();
}
