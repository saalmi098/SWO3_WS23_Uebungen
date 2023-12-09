#include <assert.h>
#include <GLFW/glfw3.h>
#include "timer.h"

static
timer_func callback;

static
double interval = TIMER_DEFAULT_INTERVAL;

extern
void timer_init(timer_func on_tick) {
	assert(on_tick);
	callback = on_tick;
	timer_reset();
}

extern
void timer_test(void) {
	if(glfwGetTime() >= interval) {
		callback();
		timer_reset();
	}
}

extern
void timer_reset(void) {
	glfwSetTime(0);
}

extern
double timer_get_interval(void) {
	return interval;
}

extern
void timer_set_interval(double itvl) {
	interval = itvl;
}
