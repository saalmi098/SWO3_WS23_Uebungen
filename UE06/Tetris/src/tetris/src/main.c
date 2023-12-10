#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timer.h"
#include "gameboard.h"
#include "renderer.h"
#include "types.h"

#define TIMER_DECREASE_FACTOR 1.5

bool gameover = false;

void on_current_tetrimino_collision(void);

void gameloop(key_t const key, action_t const action) {
	int dx = 0;
	int dy = 0;

	switch (key) {
		case key_down: dy = -1; break;
		case key_left: dx = -1; break;
		case key_right: dx = 1; break;
	}
	
	if ((key == key_up || key == key_e) && action == action_press) {
		rotate_current(true);
	}
	else if (key == key_q && action == action_press) {
		rotate_current(false);
	}
	else if (action == action_press || action == action_repeat) {
		bool move_successful = try_move_current(dx, dy);
		if (!move_successful && dx == 0) {
			on_current_tetrimino_collision();
		}
	}
}

void on_current_tetrimino_collision(void) {
	// fix tetrimino blocks at current position and spawn new tetrimino
	tetrimino current = get_current_tetrimino();
	for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
		block b = current.rotations[0].blocks[i];
		set_block_at(b.pos, b);
		if (get_max_y_of_fixed_blocks() >= GB_ROWS - 1) {
			gameover = true;
		}
	}


	bool any_row_deleted = check_and_delete_completed_rows();
	if (any_row_deleted) {
		// increase game speed
		timer_set_interval(timer_get_interval() / TIMER_DECREASE_FACTOR);
	}

	spawn_new_tetrimino();
}

void render_blocks(void) {
	tetrimino current = get_current_tetrimino();
	for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
		block b = current.rotations[0].blocks[i];
		renderer_render(b.pos, b.color);
	}

	for (int y = 0; y < GB_ROWS; y++) {
		for (int x = 0; x < GB_COLS; x++) {
			position pos = { x, y };
			block b = get_block_at(pos);
			if (!is_empty_block(b))
			{
				renderer_render(pos, b.color);
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

void init_new_game(void) {
	timer_set_interval(TIMER_DEFAULT_INTERVAL);
	timer_reset();

	gameover = false;
	init_gameboard();
	spawn_new_tetrimino();
}

int main() {
	// TODO Repo in ue05-saalmi umziehen!!!!
	renderer_init(GB_ROWS, GB_COLS, on_key_pressed);
	timer_init(on_timer_elapsed);

	srand((unsigned)time(0));
	init_new_game();

	while(renderer_open()) {
		if (gameover) {
			init_new_game();
			gameover = false;
		}

		renderer_begin_frame();

		timer_test();
	
		render_blocks();

		renderer_end_frame();
	}

	renderer_shutdown();
}