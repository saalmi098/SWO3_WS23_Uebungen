#ifndef TYPES_H
#define TYPES_H

#define NUM_TETRIMINOS 7
#define NUM_TETRIMINO_BLOCKS 4

typedef enum {
	color_black   = 0,
	color_red     = 255U <<  0U,
	color_green   = 255U <<  8U,
	color_blue    = 255U << 16U,
	color_yellow  = color_red   | color_green,
	color_magenta = color_red   | color_blue,
	color_cyan    = color_green | color_blue,
	color_orange  = color_red   | color_yellow,
	color_white   = color_red   | color_green | color_blue,
} color;

typedef struct {
	int x, y;
} position;

typedef struct {
	position pos;
	color color;
} block;

typedef struct {
	block blocks[NUM_TETRIMINO_BLOCKS];
} tetrimino;

typedef enum {
	key_down,
	key_left,
	key_right,
	key_up,
	key_q,
	key_e,
} key_t;

typedef enum {
	action_press,
	action_repeat,
	action_release,
} action_t;

typedef void(*key_callback)(key_t, action_t);

#endif
