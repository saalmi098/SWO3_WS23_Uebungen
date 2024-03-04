#pragma once

#include "./shape.h"

class draw_window final : public ml5::window {
public:
	draw_window() : ml5::window{"My Draw App"} {
	}

private:
	void on_init() override {
		add_menu("&Shape", { // &Shape ... Alt+S selects Shape menu
			{"&Ellipse", "Draws an ellipse."},
			{"&Line", "Draws a line."},
			{"&Rectangle", "Draws a rectangle."}
		});
	}

	void on_menu(ml5::menu_event const& event) override {
		if (event.get_title_and_item() == "Shape/Ellipse") {
			set_status_text("Shape/Ellipse menu selected.");
		}
	}

	void on_mouse_left_down(ml5::mouse_event const& event) override {
		wxPoint const pos{ event.get_position() };

		//m_p_shape = std::unique_ptr<shape>{ new ellipse{ wxRect{pos, pos}, *wxBLACK_PEN, *wxGREEN_BRUSH } };
		// oder einfacher:
		m_p_shape = std::make_unique<ellipse>(
			wxRect{ pos, pos }, *wxBLACK_PEN, *wxGREEN_BRUSH
		);
	}

	void on_mouse_left_up(ml5::mouse_event const& event) override {
		
	}

	void on_mouse_move(ml5::mouse_event const& event) override {
		if (m_p_shape) {
			m_p_shape->set_right_bottom(event.get_position());
		}

		refresh(); // neu zeichnen / refresh() schickt on_paint Event
	}

	void on_paint(ml5::paint_event const& event) override {
		if (m_p_shape) {
			m_p_shape->draw(event.get_context());
		}
		
		//ellipse { wxRect{0, 0, 100, 100}, *wxBLACK_PEN, *wxGREEN_BRUSH }
		//	.draw(event.get_context());
	}

	std::unique_ptr<shape> m_p_shape{};
};