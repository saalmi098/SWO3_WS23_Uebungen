#pragma once

#include "ml5/ml5.h"

class shape {
public:
	using context_t = ml5::paint_event::context_t;

	shape(wxRect const& box, wxPen const& pen, wxBrush const& brush) :
		m_box{ box }, m_brush{ brush }, m_pen{ pen } {
	}

	void draw(context_t& context) {
		context.SetPen(m_pen);
		context.SetBrush(m_brush);

		do_draw(context); // "template method pattern" (draw ... "template method" nicht virtual,
		// do_draw ... "hook method" pure virtual (=abstrakte Methode bzw. sogar dadurch abstr. Klasse)
	}

	void set_right_bottom(wxPoint const point) {
		m_box.SetRightBottom(point);
	}

protected:
	wxRect m_box{}; // bounding box
	wxBrush m_brush{};
	wxPen m_pen{};

	virtual void do_draw(context_t& context) = 0;
};

class ellipse final : public shape {
public:
	ellipse(wxRect const& box, wxPen const& pen, wxBrush const& brush) :
		shape{box, pen, brush} {
	}


private: // do_draw jetzt private ("sealed", kann nicht mehr überschrieben werden)
	virtual void do_draw(context_t& context) override {
		context.DrawEllipse(m_box);
	}
};