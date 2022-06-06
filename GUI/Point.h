#pragma once

class Point
{
public:
	constexpr inline Point() noexcept;
	constexpr inline Point(int x, int y);
	constexpr inline void set_x(int x);
	constexpr inline void set_y(int y);
	constexpr inline int get_x() const noexcept;
	constexpr inline int get_y() const noexcept;
private:
	int xp, yp;
};

constexpr inline Point::Point() noexcept : xp(-1), yp(-1) {}

constexpr inline Point::Point(int x, int y) : xp(x), yp(y) {}

constexpr inline int Point::get_x() const noexcept {
	return xp;
}

constexpr inline int Point::get_y() const noexcept {
	return yp;
}

constexpr inline void Point::set_x(int x) {
	xp = x;
}

constexpr inline void Point::set_y(int y) {
	yp = y;
}

