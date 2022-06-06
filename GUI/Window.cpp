// reference : https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)

#include "Window.h"

Window::Window()
	: m_hInstance(GetModuleHandle(nullptr)) {
	style = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_OVERLAPPEDWINDOW;
	createWindow();
	createOpenGLContext();

	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext,
	const int* attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;


typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int *piAttribIList,
        const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
wglChoosePixelFormatARB_type *wglChoosePixelFormatARB;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::set_window_title(std::string title) {
	std::wstring stemp = std::wstring(title.begin(), title.end());
	LPCWSTR sw = stemp.c_str();
	SetWindowText(m_hWnd, sw);
}

const std::string Window::get_window_title() const {
	char wnd_title[256];
	GetWindowTextA(m_hWnd, wnd_title, sizeof(wnd_title));
	std::string title(wnd_title);
	return title;
}

int Window::get_x() const noexcept {
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	return rect.left;
}

int Window::get_y() const noexcept {
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	return rect.top;
}

Rect Window::get_adjusted_window_rect(Size client_size) {
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = client_size.get_width();
	rect.bottom = client_size.get_width();

	AdjustWindowRect(&rect, style, false);

	Rect adjusted_rect = Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	return adjusted_rect;
}

Rect Window::get_window_rect() {

	RECT rect;
	if (GetWindowRect(m_hWnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		Rect window_rect = Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		return window_rect;
	}
	return Rect();
}

void Window::resize(Size client_size) {
	Rect rect = get_adjusted_window_rect(client_size);

	SetWindowPos(m_hWnd, 0, 
		rect.get_x(),
		rect.get_y(),
		rect.get_width(),
		rect.get_height(),
		SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER
	);
}

void Window::resize(int width, int height) {
	resize(Size(width, height));
}

const Size Window::get_size() {
	RECT rect;
	if (GetWindowRect(m_hWnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		return Size(width, height);
	}
	return Size();
}

void Window::setupPixelFormat() {
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size
		1,                          // version
		PFD_SUPPORT_OPENGL |        // OpenGL window
		PFD_DRAW_TO_WINDOW |        // render to window
		PFD_DOUBLEBUFFER,           // support double-buffering
		PFD_TYPE_RGBA,              // color type
		32,                         // prefered color depth
		0, 0, 0, 0, 0, 0,           // color bits (ignored)
		0,                          // no alpha buffer
		0,                          // alpha bits (ignored)
		0,                          // no accumulation buffer
		0, 0, 0, 0,                 // accum bits (ignored)
		16,                         // depth buffer
		0,                          // no stencil buffer
		0,                          // no auxiliary buffers
		PFD_MAIN_PLANE,             // main layer
		0,                          // reserved
		0, 0, 0,                    // no layer, visible, damage masks
	};

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
}

void Window::createWindow() {
	const wchar_t* CLASS_NAME = L"Window";
	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	Rect rect = get_adjusted_window_rect(Size(640, 480));

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Window",
		style,
		250,
		250,
		rect.get_width(),
		rect.get_height(),
		NULL,
		NULL,
		m_hInstance,
		NULL
	);
}

void Window::createOpenGLContext() {
	hdc = GetDC(m_hWnd);

	setupPixelFormat();

	HGLRC rc = wglCreateContext(hdc);

	wglMakeCurrent(hdc, rc);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, 1000, 1000);
	glOrtho(0, 1000, 1000, 0, 0.0, -1.0);
}

void Window::show() const {
	ShowWindow(m_hWnd, SW_SHOW);
}


void Window::paint() {
	glClearColor(255, 255, 255, 1.f);
	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT |
		GL_STENCIL_BUFFER_BIT
	);

	Painter painter = Painter();
	painter.draw_rectangle(Rect(900, 900, 100, 100));
	
	SwapBuffers(hdc);
}

Window::~Window() {
	const wchar_t* CLASS_NAME = L"Window";
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages() {
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			paint();
		}
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}