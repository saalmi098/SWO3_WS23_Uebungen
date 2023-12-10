#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <stdbool.h>
#include "types.h"
#include "renderer.h"

#define GB_ROWS 22
#define GB_COLS 11

void init_gameboard(void);
block get_block_at(position const pos);
void set_block_at(position const pos, block const b);
bool is_empty_block(block const b);
void spawn_new_tetrimino(void);
bool is_valid_position(position const pos);
tetrimino get_current_tetrimino();
bool try_move_current(int const dx, int const dy);
bool try_move(block * b, int const dx, int const dy);
void rotate_current(bool clockwise);
bool check_and_delete_completed_rows(void);
int get_max_y_of_fixed_blocks(void);

#endif
