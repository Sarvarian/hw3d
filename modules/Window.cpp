#include "Window.hpp"
#include "../resource.h"
#include "loguru/loguru.hpp"

Window::Window(const HINSTANCE hInstance, const WndProcFunc WndProc)
	: hInstance(hInstance)
{
	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 148, 150, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance
	hWnd = CreateWindowExW(
		0, pClassName,
		L"Milk",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		100, 50, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	LOG_IF_F(ERROR, !hWnd, "Creating Window Failed!");

	// show the damn window
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	if (UnregisterClassW(pClassName, hInstance))
		LOG_F(ERROR, "UnregisterClassW Failed!");
	else
		LOG_F(INFO, "UnregisterClassW Succeed!");
}
