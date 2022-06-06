#pragma once

#include "Point.h"
#include <stdlib.h>

class Rect
{
public:
	constexpr inline Rect() = default;
	constexpr inline Rect(int x, int y, int w, int h);
	constexpr inline void set_x(int x);
	constexpr inline void set_y(int y);
	constexpr inline void set_width(int w);
	constexpr inline void set_height(int h);
	constexpr inline int get_x() const noexcept;
	constexpr inline int get_y() const noexcept;
	inline int get_width() const noexcept;
	inline int get_height() const noexcept;

private:
	Point p1, p2;
};

constexpr inline Rect::Rect(int x, int y, int w, int h) {
	p1.set_x(x);
	p1.set_y(y);
	p2.set_x(x + w);
	p2.set_y(y + h);
}

constexpr inline void Rect::set_x(int x) {
	p1.set_x(x);
}

constexpr inline void Rect::set_y(int y) {
	p1.set_y(y);
}

constexpr inline void Rect::set_width(int w) {
	int x = p1.get_x() + w;
	p2.set_x(x);
}

constexpr inline void Rect::set_height(int h) {
	int y = p1.get_y() + h;
	p2.set_y(y);
}

constexpr inline int Rect::get_x() const noexcept {
	return p1.get_x();
}

constexpr inline int Rect::get_y() const noexcept {
	return p1.get_y();
}

inline int Rect::get_width() const noexcept {
	return abs(p2.get_x() - p1.get_x());
}

inline int Rect::get_height() const noexcept {
	return abs(p2.get_y() - p1.get_y());
}