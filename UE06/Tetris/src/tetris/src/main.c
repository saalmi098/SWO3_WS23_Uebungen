#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include "timer.h"
#include "gameboard.h"
#include "renderer.h"
#include "types.h"

void on_current_tetrimino_collision(void);

void gameloop(key_t const key, action_t const action) {
	int dx = 0;
	int dy = 0;

	switch (key) {
		case key_down: dy = -1; break;
		case key_left: dx = -1; break;
		case key_right: dx = 1; break;
	}

	if (key == key_up && action == action_press) {
		rotate_current_clockwise();
	} else if (action == action_press || action == action_repeat) {
		bool move_successful = try_move_current(dx, dy);
		if (!move_successful && dx == 0) {
			on_current_tetrimino_collision();
		}
	}
}

void on_current_tetrimino_collision(void) {
	// fix tetrimino blocks at current position and spawn new tetrimino
	tetrimino current = get_current_tetrimino();
	int current_rotation = get_current_rotation();
	for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
		block b = current.rotations[current_rotation].blocks[i];
		set_block_at(b.pos, b);
	}

	check_and_delete_completed_rows();

	spawn_new_tetrimino();
}

void render_blocks(void) {
	tetrimino current = get_current_tetrimino();
	int current_rotation = get_current_rotation();
	for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
		block b = current.rotations[current_rotation].blocks[i];
		renderer_render(b.pos, b.color);
	}

	for (int y = 0; y < GB_ROWS; y++) {
		for (int x = 0; x < GB_COLS; x++) {
			position pos = { x, y };
			block b = get_block_at(pos);
			if (!is_empty_block(b))
			{
				renderer_render(pos, b.color); // TODO maybe use b.pos if weird errors occur
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

	spawn_new_tetrimino();

	while(renderer_open()) {
		renderer_begin_frame();

		timer_test();
	
		render_blocks();

		renderer_end_frame();
	}

	renderer_shutdown();
}