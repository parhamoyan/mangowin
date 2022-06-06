#pragma once

#include "Window.h"
#include "Rect.h"

class Painter
{
public:
	void draw_rectangle(const Rect& rect);
	// TODO
	void draw_ellipse(const Rect& rect) {}
	void draw_rounded_rectangle() {}
};

