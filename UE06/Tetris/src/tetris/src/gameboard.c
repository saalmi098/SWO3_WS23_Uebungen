#include "gameboard.h"

gb_is_valid_position(position const pos) {
	return pos.x >= 0 && pos.x < GB_COLS
		&& pos.y >= 0 && pos.y < GB_ROWS;
}