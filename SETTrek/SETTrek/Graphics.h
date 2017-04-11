/*
* PROJECT		: SETTrek
* FILE			: Graphics.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The header file containing the class definition for the Graphics.
* CREDIT: https://www.youtube.com/user/WhatsACreel
*	Credit to the Youtuber What's A Creel for the composition of the game engine.
*/
#pragma once
#include <Windows.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
// Newly Direct2D for Windows 8.1 and later
#include <wrl.h>
#include <wrl/client.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
#include <dwrite.h>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;	// For using ComPtr



//=============================
// GRAPHIC CONSTANTS
//=============================
#define PI                      3.14159265f
#define kDefaultScreenWidth		1024
#define kDefaultScreenHeight	768

// CONSTANTS from Rastertek
#define FULL_SCREEN             false
#define VSYNC_ENABLED           false
#define SCREEN_DEPTH            1000.0f
#define SCREEN_NEAR             0.1f



//=============================
// GRAPHIC STRUCT DEFINITIONS
//=============================
struct VECTOR2
{
	float x;
	float y;
} typedef vector2;



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

	// New Direct2D 1.1
	ID2D1Factory1* d2d1Factory1;			//!< Direct2D factory - creates the tools to using Direct2D components
	ID2D1DeviceContext* d2d1Context;		//!< Direct2D device context allows for renderable targets to be drawn
	ID2D1Device* d2d1Device;				//!< Direct2D device 
	ID2D1Bitmap1* d2d1Bitmap;				//!< Direct 2D bitmap used as the render target for device context

    //===-----------------
    // DirectWrite fonts, writing
    IDWriteFactory* dwriteFactory;
    IDWriteTextFormat* dwriteTextFormat;
    IDWriteTextLayout* dwriteTextLayout;


	DXGI_PRESENT_PARAMETERS parameters;		//!< DXGI parameters settings for swap chaining

    //===-----------------
    //
    IDXGISwapChain1* dxgiSwapChain;			//!< Direct2D swap chain

    // Direct3Dx11 objects
    ID3D11Device1* d3d11Device;				        //!< Direct3D device
    ID3D11DeviceContext1* d3d11Context;		        //!< Direct3D context device derived for Direct2D context device
    ID3D11RenderTargetView* _RenderTargetView;      //!<
    ID3D11Texture2D*        _depthStencilBuffer;    //!<
    ID3D11DepthStencilState* _depthStencilState;    //!<
    ID3D11DepthStencilView* _depthStencilView;      //!<
    ID3D11RasterizerState*  _rasterState;           //!<
    XMMATRIX _projectionMatrix;                     //!<
    XMMATRIX _worldMatrix;                          //!<
    XMMATRIX _orthoMatrix;                          //!<

    //
    //===-----------------
    

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
    bool InitDirectWrite(void);
	void Resize(HWND windowHandle);

	void BeginDraw(void) { d2d1Context->BeginDraw(); }
	void EndDraw(void);
    void RenderText(wstring text, D2D1_RECT_F area, D2D1_COLOR_F fontColor);

	ID2D1DeviceContext* GetDeviceContext(void);
    IDWriteTextFormat* GetTextFormat(void);

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a = 1.0f);
	void DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a);
    void DrawLine(float pX1, float pY1, float pX2, float pY2, float r, float g, float b, float thickness = 1.0f);
};
