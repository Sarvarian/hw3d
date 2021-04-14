#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <Windows.h>
#include <math.h>
#include "resource.h"
#include "loguru/loguru.hpp"
#include "loguru/loguru.cpp"
using namespace loguru;

HWND build_window(HINSTANCE hInstance, LPCWCHAR pClassName);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


int main(int argc, char** argv)
{
	constexpr LPCWCHAR pClassName = L"hw3d Oppai";
	constexpr double max_frame_delay = (1. / 30.) * 1000.;
	const HMODULE handle = GetModuleHandle(NULL);
	FILETIME frame_begin_time = { 0 };
	FILETIME frame_end_time = { 0 };
	ULARGE_INTEGER ftc_first_time = { 0 };
	ULARGE_INTEGER ftc_second_time = { 0 };
	double frame_time = 0;
	double delta = 0;

	MSG msg = { 0 };
	BOOL gResult = 0;

	loguru::init(argc, argv);
	HWND hWnd = build_window(handle, pClassName);
	GetSystemTimeAsFileTime(&frame_begin_time);
	GetSystemTimeAsFileTime(&frame_end_time);
	

	// message bump
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

		// Start Frame
		GetSystemTimeAsFileTime(&frame_begin_time);

		// Loop Begin


		// Calculating delta
		ftc_first_time.HighPart = frame_end_time.dwHighDateTime;
		ftc_first_time.LowPart = frame_end_time.dwLowDateTime;
		FILETIME pre_delta_time;
		GetSystemTimeAsFileTime(&pre_delta_time);
		ftc_second_time.HighPart = pre_delta_time.dwHighDateTime;
		ftc_second_time.LowPart = pre_delta_time.dwLowDateTime;
		double delta = (ftc_second_time.QuadPart - ftc_first_time.QuadPart) / 10000.;

		// End Frame
		GetSystemTimeAsFileTime(&frame_end_time);

		// Calculating frame_time
		ftc_first_time.HighPart = frame_begin_time.dwHighDateTime;
		ftc_first_time.LowPart = frame_begin_time.dwLowDateTime;
		ftc_second_time.HighPart = frame_end_time.dwHighDateTime;
		ftc_second_time.LowPart = frame_end_time.dwLowDateTime;
		frame_time = (ftc_second_time.QuadPart - ftc_first_time.QuadPart) / 10000.;
#ifdef _DEBUG
		std::cout << delta / 1000. << std::endl;
#endif // _DEBUG

		//LOG_s(INFO) << "Hello";

		// Loop End
		Sleep((DWORD)std::clamp(max_frame_delay - frame_time, 0., max_frame_delay));
	}

	UnregisterClassW(pClassName, handle);

	if (gResult == -1)
		return -1;
	else
		return msg.wParam;
}

HWND build_window(HINSTANCE hInstance, LPCWCHAR pClassName)
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
