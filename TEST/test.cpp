#include "pch.h"
#include "../GUI/Point.h"

TEST(PointTest, ParametrizedConstructor) {
	Point p(1, 2);

	EXPECT_EQ(p.get_x(), 1);
	EXPECT_EQ(p.get_y(), 2);
}