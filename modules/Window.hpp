#pragma once
#include <Windows.h>

typedef LRESULT(*WndProcFunc) (HWND, UINT, WPARAM, LPARAM);

struct Window
{
	static constexpr LPCWCHAR pClassName = L"hw3d Oppai";
	const HINSTANCE hInstance;
	HWND hWnd;

	Window(const HINSTANCE hInstance, const WndProcFunc WndProc);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};