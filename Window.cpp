#include "Window.hpp"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static LPSTR title[500];

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_CHAR:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


HWND build_window(HINSTANCE hInstance, LPCWCHAR pClassName) {
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
	HWND hWnd = CreateWindowExW(
		0, pClassName,
		L"Milk",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		100, 50, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// show the damn window
	ShowWindow(hWnd, SW_SHOW);

	return hWnd;
}


int loop(HINSTANCE hInstance, LPCWCHAR pClassName)
{
	// message bump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	UnregisterClassW(pClassName, hInstance);

	if (gResult == -1)
		return -1;
	else
		return msg.wParam;
}


