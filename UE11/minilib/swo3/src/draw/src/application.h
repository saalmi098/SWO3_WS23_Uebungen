#pragma once

#include <ml5/ml5.h>
#include "./window.h"

class draw_application final : public ml5::application {
	std::unique_ptr<ml5::window> make_window() const override {
		return std::unique_ptr<ml5::window> {new draw_window{}};
	}
};