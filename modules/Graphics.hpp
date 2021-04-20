#pragma once
#include <d3d11.h>

struct Graphics {
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwap;
	ID3D11DeviceContext* pContext;

	Graphics(const HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
};
