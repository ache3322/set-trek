/*
* PROJECT		: SETTrek
* FILE			: Graphics.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The header file containing the class definition for the Graphics.
*/
#pragma once
#include <Windows.h>

// Newly Direct2D for Windows 8.1 and later
#include <wrl.h>
#include <wrl/client.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
using namespace Microsoft::WRL;	// For using ComPtr


/**
* \class Graphics
* \brief
*/
class Graphics
{
private:

	// Previous things....
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!

	// Direct3Dx11 objects
	ID3D11Device1* d3d11Device;				//!<
	ID3D11DeviceContext1* d3d11Context;		//!<

	// New Direct2D 1.1
	ID2D1Factory1* d2d1Factory1;			//!<
	ID2D1DeviceContext* d2d1Context;		//!<
	ID2D1Device* d2d1Device;				//!<
	IDXGISwapChain1* dxgiSwapChain;			//!<
	ID2D1Bitmap1* d2d1Bitmap;				//!< Direct 2D bitmap used as the render target for device context

	DXGI_PRESENT_PARAMETERS parameters;

public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw(void) { d2d1Context->BeginDraw(); }
	void EndDraw(void);
	ID2D1DeviceContext* GetDeviceContext(void);

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a);
};
