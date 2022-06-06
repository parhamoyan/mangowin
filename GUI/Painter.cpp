#include "Painter.h"

void Painter::draw_rectangle(const Rect& rect)
{
	glBegin(GL_POLYGON);
		glColor3ub(225, 171, 0);
		glVertex2i(rect.get_x(), rect.get_y());
		glVertex2i(rect.get_x() + rect.get_width(), rect.get_y());
		glVertex2i(rect.get_x() + rect.get_width(), rect.get_y() + rect.get_height());
		glVertex2i(rect.get_x(), rect.get_y() + rect.get_height());
	glEnd();

	glFlush(); // Render now
}
