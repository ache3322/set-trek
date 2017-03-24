/*
* PROJECT		: SETTrek
* FILE			: Graphics.cpp
* PROGRAMMER	:
* DATE			: 2017/01/25
* DESCRIPTION	: The CPP file contains the implementation for the Graphics class. Examples
*			like instantiating D2D1 COM objects, initialization, etc.
*/
#include "Graphics.h"


/**
* \brief Basic constructor for the Graphics class.
* \details All the private data members are set to a safe value.
*/
Graphics::Graphics()
{
	brush = NULL;

	d2d1Factory1 = NULL;
	d2d1Context = NULL;
	d2d1Device = NULL;
	d2d1Bitmap = NULL;

	parameters.DirtyRectsCount = 0;
	parameters.pDirtyRects = nullptr;
	parameters.pScrollRect = nullptr;
	parameters.pScrollOffset = nullptr;

    // Direct3D setting
    dxgiSwapChain = NULL;
    d3d11Device = NULL;
    d3d11Context = NULL;
    _RenderTargetView = NULL;
    _depthStencilBuffer = NULL;
    _depthStencilState = NULL;
    _depthStencilView = NULL;
    _rasterState = NULL;
}

/**
* \brief Destructor for Graphics class.
* \details Note that all COM objects must be 'released'. The COM objects from
*	the Direct2D library.
*/
Graphics::~Graphics()
{
	if (d3d11Device) d3d11Device->Release();
	if (d3d11Context) d3d11Context->Release();
	if (d2d1Factory1) d2d1Factory1->Release();
	if (d2d1Context) d2d1Context->Release();
	if (d2d1Device) d2d1Device->Release();
	if (dxgiSwapChain) dxgiSwapChain->Release();
	if (d2d1Bitmap) d2d1Bitmap->Release();
}


/**
* \brief Initialize the Graphics object and all COM components.
* \details Initialize the necessary resources to use the Direct2D graphics.
*		It includes binding the client's window to the COM.<br/>
* Credit: https://katyscode.wordpress.com/2013/01/23/migrating-existing-direct2d-applications-to-use-direct2d-1-1-functionality-in-windows-7/
* \param windowHandle - HWND - A handle to the client's 
* \return bool : true if the Graphics was initialized, else return false.
*/
bool Graphics::Init(HWND windowHandle)
{
	CoInitialize(nullptr);

	//=====================
	//-------------------
	//--- VARIABLE DECLARATION

	// Creating Direct3D device and context - enables
	// us to use functionalities to be supported in Direct2D
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	ComPtr<IDXGIDevice> dxgiDevice;
	
	//=======================
	//----------------------

	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	// Create D2D1 object to be used to create D2D1 resources
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		__uuidof(ID2D1Factory1),
		&options,
		reinterpret_cast<void **>(&d2d1Factory1));
	if (hr != S_OK) return false;

	// Acquire the client window size - for rendering targets on this dimension
	RECT rect;
	GetClientRect(windowHandle, &rect);
	D2D1_SIZE_U clientSize = D2D1::SizeU(rect.right, rect.bottom);

	// Create a render target to render window
	hr = d2d1Factory1->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, clientSize),
		(ID2D1HwndRenderTarget **)&d2d1Context);
	if (hr != S_OK) return false;

	// Set feature levels supported by our application
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	
	// Adding this flag supports different color channels
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// Creating the Direct32 device
	hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		creationFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&device,
		NULL,
		&context
	);
	if (hr != S_OK) return false;

	// Fetching underlying interfaces for the D3D11
	hr = device.Get()->QueryInterface(__uuidof(ID3D11Device1), (void **)&d3d11Device);
	hr = context.Get()->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&d3d11Context);
	if (hr != S_OK) return false;

	// Fetching the underlying DXGI device
	hr = d3d11Device->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);
	if (hr != S_OK) return false;

	// Now create the Direct2D context
	hr = d2d1Factory1->CreateDevice(dxgiDevice.Get(), &d2d1Device);
	if (hr != S_OK) return false;

	// Get the corresponding device context object
	hr = d2d1Device->CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		&d2d1Context);
	if (hr != S_OK) return false;


	//=====================
	//-------------------
	//--- SWAP CHAINING

	// Variables for Swap Chaining
	ComPtr<IDXGIAdapter> dxgiAdapter;
	ComPtr<IDXGIFactory2> dxgiFactory;
	FLOAT dpiX = 0.f;
	FLOAT dpiY = 0.f;

	// 1. Getting the DXGI Factory object and adapter
	dxgiDevice->GetAdapter(&dxgiAdapter);
	if (hr != S_OK) return false;

	// 2. Get an instance of the DXGI factory
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
	if (hr != S_OK) return false;

	// 3. Defining and describing the swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
    swapChainDesc.BufferCount = 1;                          // use double buffering to enable flip (2 - default)
	swapChainDesc.Width = 0;                                // use automatic sizing
	swapChainDesc.Height = 0;		                        // determined by client size
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SampleDesc.Count = 1;                  // don't use multi-sampling
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discarding back buffer contents
    swapChainDesc.Flags = 0;
	swapChainDesc.Stereo = false;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;

	// 4. Create the Swap Chain for the Window Handle
	hr = dxgiFactory->CreateSwapChainForHwnd(
		d3d11Device,
		windowHandle,
		&swapChainDesc,
		nullptr,
		nullptr,
		&dxgiSwapChain
	);
	if (hr != S_OK) return false;

	// 5. Get the backbuffer
	ComPtr<IDXGISurface> dxgiBackBuffer;
	dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
	if (hr != S_OK) return false;

	// 6. Creation of a bitmap needed to be the render target
	d2d1Factory1->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			dpiX,
			dpiY
		);

	d2d1Context->CreateBitmapFromDxgiSurface(
		dxgiBackBuffer.Get(),
		bitmapProperties,
		&d2d1Bitmap);
	if (hr != S_OK) return false;

	// 7. Finally! Now set the bitmap as the Device Context's render target
	d2d1Context->SetTarget(d2d1Bitmap);
	//---
	//-------------------
	//=====================

	// Create a solid brush from the DeviceContext
	hr = d2d1Context->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (hr != S_OK) return false;


    //=====================
    //-------------------
    //--- INIT DIRECTX11
    //D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE)
    //ID3D11Texture2D* backBufferPtr;
    //dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);

    //d3d11Device->CreateRenderTargetView(backBufferPtr, NULL, &_RenderTargetView);

    //// Releasing the back buffer since it is no longer needed
    //backBufferPtr->Release();
    //backBufferPtr = nullptr;


    //D3D11_TEXTURE2D_DESC depthBufferDesc = { 0 };
    //// Set-up the description of the depth buffer
    //depthBufferDesc.Width = clientSize.width;
    //depthBufferDesc.Height = clientSize.height;
    //depthBufferDesc.MipLevels = 1;
    //depthBufferDesc.ArraySize = 1;
    //depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    //depthBufferDesc.SampleDesc.Count = 1;
    //depthBufferDesc.SampleDesc.Quality = 0;
    //depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    //depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    //depthBufferDesc.CPUAccessFlags = 0;
    //depthBufferDesc.MiscFlags = 0;

    //d3d11Device->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);


    //// Set up the description of the stencil state
    //D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
    //depthStencilDesc.DepthEnable = true;
    //depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    //depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    //
    //depthStencilDesc.StencilEnable = true;
    //depthStencilDesc.StencilReadMask = 0xFF;
    //depthStencilDesc.StencilWriteMask = 0xFF;

    //// Stencil operations if pixel is front-facing.
    //depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    //depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    //depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    //depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    //// Stencil operations if pixel is back-facing.
    //depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    //depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    //depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    //depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    //// CREATE
    //d3d11Device->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);

    //d3d11Context->OMSetDepthStencilState(_depthStencilState, 1);


    //D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    //// Initialize the depth stencil view.
    //ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
    //// Set up the depth stencil view description.
    //depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    //depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    //depthStencilViewDesc.Texture2D.MipSlice = 0;

    //d3d11Device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);

    //// Bind the render target view and depth stencil buffer to the output render pipeline.
    //d3d11Context->OMSetRenderTargets(1, &_RenderTargetView, _depthStencilView);


    //// Setup the raster description which will determine how and what polygons will be drawn.
    //D3D11_RASTERIZER_DESC rasterDesc;
    //rasterDesc.AntialiasedLineEnable = false;
    //rasterDesc.CullMode = D3D11_CULL_BACK;
    //rasterDesc.DepthBias = 0;
    //rasterDesc.DepthBiasClamp = 0.0f;
    //rasterDesc.DepthClipEnable = true;
    //rasterDesc.FillMode = D3D11_FILL_SOLID;
    //rasterDesc.FrontCounterClockwise = false;
    //rasterDesc.MultisampleEnable = false;
    //rasterDesc.ScissorEnable = false;
    //rasterDesc.SlopeScaledDepthBias = 0.0f;

    //// Create the rasterizer state from the description we just filled out.
    //d3d11Device->CreateRasterizerState(&rasterDesc, &_rasterState);
    //// Set the rasterizer state.
    //d3d11Context->RSSetState(_rasterState);


    //D3D11_VIEWPORT viewport;
    //// Setup the viewport for rendering.
    //viewport.Width = (float)clientSize.width;
    //viewport.Height = (float)clientSize.height;
    //viewport.MinDepth = 0.0f;
    //viewport.MaxDepth = 1.0f;
    //viewport.TopLeftX = 0.0f;
    //viewport.TopLeftY = 0.0f;

    //// Create the viewport.
    //d3d11Context->RSSetViewports(1, &viewport);


    //// Setup the projection matrix.
    //float fieldOfView = 0.f; 
    //float screenAspect = 0.f;
    //fieldOfView = 3.141592654f / 4.0f;
    //screenAspect = (float)clientSize.width / (float)clientSize.height;

    //// Create the projection matrix for 3D rendering.
    //_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);


    //// Initialize the world matrix to the identity matrix.
    //_worldMatrix = XMMatrixIdentity();


    //// Create an orthographic projection matrix for 2D rendering.
    //_orthoMatrix = XMMatrixOrthographicLH((float)clientSize.width, (float)clientSize.height, SCREEN_NEAR, SCREEN_DEPTH);

	return true;
}


/**
* \brief
* \details
* \param
* \return void
*/
void Graphics::Resize(HWND windowHandle)
{
	ComPtr<IDXGIDevice> dxgiDevice;

	// Fetching the underlying DXGI device
	d3d11Device->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);

	// Variables for Swap Chaining
	ComPtr<IDXGIAdapter> dxgiAdapter;
	ComPtr<IDXGIFactory2> dxgiFactory;

	// 1. Getting the DXGI Factory object and adapter
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// 2. Get an instance of the DXGI factory
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	// 3. Defining and describing the swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;        // use automatic sizing
	swapChainDesc.Height = 0;		// determined by client size
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;						 // Use double buffering to enable flip
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Disabling the swap effects
	swapChainDesc.Flags = 0;

	// 5. Get the backbuffer
	ComPtr<IDXGISurface> dxgiBackBuffer;
	dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));


	FLOAT dpiX = 0.f;
	FLOAT dpiY = 0.f;
	// 6. Creation of a bitmap needed to be the render target
	d2d1Factory1->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			dpiX,
			dpiY
		);

	d2d1Context->CreateBitmapFromDxgiSurface(
		dxgiBackBuffer.Get(),
		bitmapProperties,
		&d2d1Bitmap);

	// 7. Finally! Now set the new bitmap as the Device Context's render target
	d2d1Context->SetTarget(d2d1Bitmap);
}


/**
* \brief End drawing the graphics.
* \details After ending the draw, the render target
*	must be swapped chained.
* \param void
* \return void
*/
void Graphics::EndDraw(void) 
{ 
	d2d1Context->EndDraw();

	// Long time ago, in Direct2D the render target
	// was automatically swapped chained. However, with
	// the new Direct2D we must manually do it
	dxgiSwapChain->Present1(1, 0, &parameters);
}


/**
* \brief Get the device context target.
* \details The DeviceContext expands upon the RenderTarget. It provides
*	the same methods, but even more. You can use the DeviceContext for effects.
* \return ID2D1DeviceContext* - A reference to the device context target.
*/
ID2D1DeviceContext* Graphics::GetDeviceContext(void)
{
	return d2d1Context;
}


/**
* \brief Clear the redner target (client screen) with a RGB color.
* \details Calls upon a D2D1 method to clear the screen.
* \param r - float - The red channel
* \param g - float - The green channel
* \param b - float - The blue channel
*/
void Graphics::ClearScreen(float r, float g, float b) 
{
	// Clear() takes in a D2D1_COLOR_F*
	d2d1Context->Clear(D2D1::ColorF(r, g, b));
}


/**
* \brief Draws a circle
* \details The DrawCircle method sets the color brush for the shape. The shape
*		that is drawn is for the Ellipse.
* \param x - float - The x location of the circle
* \param y - float - The y location of the circle
* \param radius - float - The radius of the circle
* \param r - float - The red channel
* \param g - float - The green channel
* \param b - float - The blue channel
* \param a - float - The alpha channel
*/
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	// Render the shape on the target...
	// Ellipse takes a position (x,y); width; height; brush; and brush stroke
	d2d1Context->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);	

}


/**
* \brief Draws a rectangle.
* \param left - float - The upper-left corner of the rectangle (x1)
* \param top - float - The upper-top corner of the rectangle (y1)
* \param right - float - The lower-right corner of the rectangle (x2)
* \param bottom - float - The lower-bottom corner of the rectangle (y2)
* \param r - float - The red channel
* \param g - float - The green channel
* \param b - float - The blue channel
* \param a - float - The alpha channel
*/
void Graphics::DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	// Render the shape on the target...
	d2d1Context->DrawRectangle(D2D1::Rect(left, top, right, bottom), brush, 3.0f);
}