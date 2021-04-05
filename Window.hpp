#pragma once
#include "Headers.hpp"
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND build_window(HINSTANCE hInstance, LPCWCHAR pClassName);
int loop(HINSTANCE hInstance, LPCWCHAR pClassName);