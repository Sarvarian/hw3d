#include <Windows.h>
#include <d3d11.h>
#include <algorithm>
#include <optional>
#include "resource.h"
#include "modules/loguru/loguru.hpp"
#include "modules/loguru/loguru.cpp"
#include "modules/Window.hpp"
#include "modules/Graphics.hpp"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int Play(const HWND hWnd);


int main(int argc, char** argv)
{
	loguru::init(argc, argv);
	Window window{ GetModuleHandle(NULL), WndProc };
	Graphics graphics = Graphics(window.hWnd);
	int res = Play(window.hWnd);
	return res;
}

LRESULT CALLBACK WndProc(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
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

std::optional<int> ProcessMessages()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

int Play(const HWND hWnd)
{
	constexpr double max_frame_delay = (1. / 60.) * 1000.;
	FILETIME frame_begin_time = { 0 };
	FILETIME frame_end_time = { 0 };
	ULARGE_INTEGER ftc_first_time = { 0 };
	ULARGE_INTEGER ftc_second_time = { 0 };
	double frame_time = 0;
	double delta = 0;

	GetSystemTimeAsFileTime(&frame_begin_time);
	GetSystemTimeAsFileTime(&frame_end_time);

	while (true)
	{
		if (const std::optional<int> ecode = ProcessMessages())
			return *ecode;

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
		{
			char buf[_CVTBUFSIZE];
			int err;

			err = _gcvt_s(buf, _CVTBUFSIZE, delta, 5);

			if (err != 0)
			{
				printf("_gcvt_s failed with error code %d\n", err);
				exit(1);
			}

			SetWindowTextA(hWnd, buf);
		}
#endif // _DEBUG

		//LOG_s(INFO) << "Hello";

		// Loop End
		Sleep((DWORD)std::clamp(max_frame_delay - frame_time, 0., max_frame_delay));
	}
}