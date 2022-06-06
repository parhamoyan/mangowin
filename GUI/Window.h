#pragma once
#include <Windows.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <string>
#include <iostream>
#include <cassert>
#include "Size.h"
#include "Painter.h"
#include "Rect.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM uParam, LPARAM lParam);

class Window
{
public:
	Window();
	//Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void set_window_title(std::string title);
	const std::string get_window_title() const;
	void resize(Size size);
	void resize(int width, int height);
	const Size get_size();
	int get_x() const noexcept;
	int get_y() const noexcept;
	void show() const;
	void paint();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC hdc;
	std::string window_title;
	Size size;
	DWORD style;
	void setupPixelFormat();
	void createOpenGLContext();
	void createWindow();
	Rect get_window_rect();
	Rect get_adjusted_window_rect(Size client_size);
};
