/*
* PROJECT		: SETTrek
* FILE			: D3Class.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The header file containing the class definition for the Direct3D class.
* CREDIT        : http://www.rastertek.com/dx11s2tut04.html
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
// From Rasterek tutorial
#include <DirectXMath.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace Microsoft::WRL;	// For using ComPtr



//=============================
// D3Class CONSTANTS
//=============================
#define SCREEN_DEPTH        1000.0f
#define SCREEN_NEAR         0.1



//=============================
// D3CLASS CLASS DEFINITION
//=============================
/**
* \class D3Class
* \brief The D3Class uses the Direct3D library and methods
*/
class D3Class
{
private:

    // New Direct2D 1.1
    ID2D1Factory1* _d2Factory1;			//!< Direct2D factory - creates the tools to using Direct2D components
    ID2D1DeviceContext* d2d1Context;		//!< Direct2D device context allows for renderable targets to be drawn
    ID2D1Device* d2d1Device;				//!< Direct2D device 
    ID2D1Bitmap1* d2d1Bitmap;				//!< Direct 2D bitmap used as the render target for device context

    DXGI_PRESENT_PARAMETERS parameters;		//!< DXGI parameters settings for swap chaining

    //===-----------------
    // Direct3D variables
    IDXGISwapChain* _swapChain;
    IDXGISwapChain1* _swapChain1;       			//!< Direct2D swap chain

    // Direct3Dx11 objects
    ID3D11Device1*              _device3d;				//!< Direct3D device
    ID3D11DeviceContext1*       _deviceContext1;		//!< Direct3D context device derived for Direct2D context device
    ID3D11RenderTargetView*     _renderTargetView;      //!<

    ID3D11Texture2D*            _depthStencilBuffer;    //!<
    ID3D11DepthStencilState*    _depthStencilState;     //!<
    ID3D11DepthStencilView*     _depthStencilView;      //!<    
    ID3D11RasterizerState*      _rasterState;           //!<
    XMMATRIX _projectionMatrix;                         //!<
    XMMATRIX _worldMatrix;                              //!<
    XMMATRIX _orthoMatrix;                              //!<


    D3D_DRIVER_TYPE _driverType;
    D3D_FEATURE_LEVEL _featureLevel;
    //
    //===-----------------


public:

    /*-Constructors-*/
    //------------------
    D3Class();

    /*-Deconstructors-*/
    //------------------
    ~D3Class();

    /*-General Methods-*/
    //------------------
    bool Init(HWND windowHandle);

    void BeginDraw(void) { d2d1Context->BeginDraw(); }
    void EndDraw(void);
    ID2D1DeviceContext* GetDeviceContext(void);

    /*-Direct3D Methods-*/
    //------------------
    void BeginRender(void);
    void EndRender(void);

    ID3D11Device1* GetDevice3D(void);
    ID3D11DeviceContext1* GetDeviceContext3D(void);


    /*-Matrix Methods-*/
    //------------------
    void GetProjectionMatrix(XMMATRIX&);
    void GetWorldMatrix(XMMATRIX&);
    void GetOrthoMatrix(XMMATRIX&);
};