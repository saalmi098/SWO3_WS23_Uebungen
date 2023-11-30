#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>
#include "types.h"

void renderer_init(int rows, int cols, key_callback callback);
void renderer_shutdown(void);

bool renderer_open(void);

void renderer_begin_frame(void);
void renderer_end_frame(void);

void renderer_render(const position pos, color color);

#endif
