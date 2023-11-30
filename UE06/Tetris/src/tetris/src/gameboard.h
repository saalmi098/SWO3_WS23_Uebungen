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
void spawn_new_block(void);
bool is_valid_position(position const pos);
block get_current_block();
bool try_move_current(int const dx, int const dy);
bool try_move(block * b, int const dx, int const dy);

#endif
