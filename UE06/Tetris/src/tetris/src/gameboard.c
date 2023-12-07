#include <stdlib.h>
#include <stdio.h> // TODO Delete
#include <stdbool.h>
#include <assert.h>
#include "gameboard.h"
#include "types.h"

tetrimino current;
const tetrimino tetriminos[NUM_TETRIMINOS];

const block empty_block = { { -1, -1 }, color_black }; // representation for "no block" at this position
block fixedBlocks[GB_ROWS * GB_COLS];

bool is_row_completed(int row);
bool can_move(block const b, int const dx, int const dy);

void init_gameboard(void) {
	for (int y = 0; y < GB_ROWS; y++) {
		for (int x = 0; x < GB_COLS; x++) {
			position pos = { x, y };
			set_block_at(pos, empty_block);
		}
	}
}

block get_block_at(position const pos) {
	assert(pos.y >= 0 && pos.y < GB_ROWS);
	assert(pos.x >= 0 && pos.x < GB_COLS);
	return fixedBlocks[pos.y * GB_COLS + pos.x];
}

void set_block_at(position const pos, block const b) {
	assert(pos.y >= 0 && pos.y < GB_ROWS);
	assert(pos.x >= 0 && pos.x < GB_COLS);
	fixedBlocks[pos.y * GB_COLS + pos.x] = b;
}

bool is_empty_block(block const b) {
	return b.pos.x == empty_block.pos.x && b.pos.y == empty_block.pos.y
		&& b.color == empty_block.color;
}

void spawn_new_tetrimino(void) {
	int idx = rand() % NUM_TETRIMINOS;
	
	for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
		current.blocks[i] = tetriminos[idx].blocks[i];
		current.blocks[i].pos.x += GB_COLS / 2;
		current.blocks[i].pos.y = GB_ROWS - 1 - tetriminos[idx].blocks[i].pos.y;
	}
}

tetrimino get_current_tetrimino(void) {
	return current;
}

bool is_valid_position(position const pos) {
	bool inBoundaries = pos.x >= 0 && pos.x < GB_COLS && pos.y >= 0 && pos.y < GB_ROWS;
	if (!inBoundaries)
		return false;

	// TODO Exact collision detection
	block b = get_block_at(pos);
	return is_empty_block(b);
}

bool try_move_current(int const dx, int const dy) {
	bool can_move_tetrimino = true;
	for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
		if (!can_move(current.blocks[i], dx, dy)) {
			can_move_tetrimino = false;
			break;
		}
	}

	if (can_move_tetrimino) {
		for (int i = 0; i < NUM_TETRIMINO_BLOCKS; i++) {
			try_move(&current.blocks[i], dx, dy);
		}
	}
	
	return can_move_tetrimino;
}

bool try_move(block* b, int const dx, int const dy) {
	assert(b != NULL);
	position pos = b->pos;
	pos.x += dx;
	pos.y += dy;

	if (is_valid_position(pos)) {
		b->pos = pos;
		return true;
	}

	return false;
}

bool can_move(block const b, int const dx, int const dy) {
	position pos = b.pos;
	pos.x += dx;
	pos.y += dy;

	return is_valid_position(pos);
}

bool is_row_completed(int row) {
	for (int col = 0; col < GB_COLS; col++) {
		position pos = { col, row };
		block b = get_block_at(pos);
		if (is_empty_block(b))
		{
			return false;
		}
	}

	return true;
}

void check_and_delete_completed_rows(void) {
	int row = 0;
	int const highest_row = GB_ROWS - 1; // TODO Performance: get_highest_row() or new global variable
	while (row <= highest_row) {
		if (is_row_completed(row)) {
			// clear row
			for (int col = 0; col < GB_COLS; col++) {
				position pos = { col, row };
				set_block_at(pos, empty_block);
			}

			// move all blocks above down
			for (int tmp_row = row + 1; tmp_row <= highest_row; tmp_row++) {
				for (int tmp_col = 0; tmp_col < GB_COLS; tmp_col++) {
					position tmp_pos = { tmp_col, tmp_row };
					block tmp_b = get_block_at(tmp_pos);
					if (!is_empty_block(tmp_b)) {
						// free old pos
						set_block_at(tmp_pos, empty_block);
						
						// set new pos
						position new_pos = { tmp_col, tmp_row - 1 };
						tmp_b.pos = new_pos;
						set_block_at(new_pos, tmp_b);
					}
				}
			}
		}
		else {
			row++;
		}
	}
}

const tetrimino tetriminos[NUM_TETRIMINOS] = {
	// I
	{
		{ { { 0, 0 }, color_cyan },
		  { { 0, 1 }, color_cyan },
		  { { 0, 2 }, color_cyan },
		  { { 0, 3 }, color_cyan } }
	},
	// J
	{
		{ { { 0, 0 }, color_blue },
		  { { 0, 1 }, color_blue },
		  { { 0, 2 }, color_blue },
		  { { 1, 2 }, color_blue } }
	},
	// L
	{
		{ { { 1, 0 }, color_orange },
		  { { 1, 1 }, color_orange },
		  { { 1, 2 }, color_orange },
		  { { 0, 2 }, color_orange } }
	},
	// O
	{
		{ { { 0, 0 }, color_yellow },
		  { { 1, 0 }, color_yellow },
		  { { 0, 1 }, color_yellow },
		  { { 1, 1 }, color_yellow } }
	},
	// S
	{
		{ { { 1, 0 }, color_green },
		  { { 2, 0 }, color_green },
		  { { 0, 1 }, color_green },
		  { { 1, 1 }, color_green } }
	},
	// T
	{
		{ { { 1, 0 }, color_magenta },
		  { { 0, 1 }, color_magenta },
		  { { 1, 1 }, color_magenta },
		  { { 2, 1 }, color_magenta } }
	},
	// Z
	{
		{ { { 0, 0 }, color_red },
		  { { 1, 0 }, color_red },
		  { { 1, 1 }, color_red },
		  { { 2, 1 }, color_red } }
	}
};