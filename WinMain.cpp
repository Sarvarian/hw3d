#include "Headers.hpp"

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPervInstance,
	LPSTR		lpCmdLine,
	int			cCmdShow
)
{
	const auto pClassName = L"hw3d Oppai";
	HWND hWnd = build_window(hInstance, pClassName);
	//MessageBox(hWnd, L"Hello", L"Error", 0);
	return loop(hInstance, pClassName);
}

