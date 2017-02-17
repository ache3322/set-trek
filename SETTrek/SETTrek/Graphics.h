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
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
using namespace Microsoft::WRL;	// For using ComPtr



//=============================
// GRAPHIC CONSTANTS
//=============================
#define kDefaultScreenWidth		1024
#define kDefaultScreenHeight	768



/**
* \class Graphics
* \brief The Graphics class provides the capabilities to utilize the Direct2D library.
* \details The class provides the tools and abilities to use the Direct2D 1.1 library.
*	It encapsulates the Direct2D device context, allowing images to be drawn to a target.
*/
class Graphics
{
private:

	// Previous things....
	ID2D1SolidColorBrush* brush;

	// Direct3Dx11 objects
	ID3D11Device1* d3d11Device;				//!< Direct3D device
	ID3D11DeviceContext1* d3d11Context;		//!< Direct3D context device derived for Direct2D context device

	// New Direct2D 1.1
	ID2D1Factory1* d2d1Factory1;			//!< Direct2D factory - creates the tools to using Direct2D components
	ID2D1DeviceContext* d2d1Context;		//!< Direct2D device context allows for renderable targets to be drawn
	ID2D1Device* d2d1Device;				//!< Direct2D device 
	IDXGISwapChain1* dxgiSwapChain;			//!< Direct2D swap chain
	ID2D1Bitmap1* d2d1Bitmap;				//!< Direct 2D bitmap used as the render target for device context

	DXGI_PRESENT_PARAMETERS parameters;		//!< DXGI parameters settings for swap chaining

public:

	/*-Constructors-*/
	//------------------
	Graphics();

	/*-Deconstructors-*/
	//------------------
	~Graphics();

	/*-General Methods-*/
	//------------------
	bool Init(HWND windowHandle);
	void Resize(HWND windowHandle);

	void BeginDraw(void) { d2d1Context->BeginDraw(); }
	void EndDraw(void);
	ID2D1DeviceContext* GetDeviceContext(void);

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a);
};
