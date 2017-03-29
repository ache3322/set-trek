/*
* PROJECT		: SETTrek
* FILE			: D3Class.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The CPP file contains the implementation for the D3DClass class. Examples
*			like instantiating D2D1 COM objects, initialization, etc.
*/
#include "D3Class.h"



/**
* \brief Basic constructor for the D3Class class.
* \details All the private data members are set to a safe value.
*/
D3Class::D3Class()
{
    _d2Factory1 = NULL;
    d2d1Context = NULL;
    d2d1Device = NULL;
    d2d1Bitmap = NULL;

    parameters.DirtyRectsCount = 0;
    parameters.pDirtyRects = nullptr;
    parameters.pScrollRect = nullptr;
    parameters.pScrollOffset = nullptr;

    // Direct3D setting
    _swapChain = NULL;
    _swapChain1 = NULL;
    _device3d = NULL;
    _deviceContext1 = NULL;
    _renderTargetView = NULL;

    _vertexShader = nullptr;
    _vertexLayout = nullptr;
    _pVertexBuffer = nullptr;

    _depthStencilBuffer = NULL;
    _depthStencilState = NULL;
    _depthStencilView = NULL;
    _rasterState = NULL;

    _driverType = D3D_DRIVER_TYPE_NULL;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
}


/**
* \brief Destructor for this class.
* \details Note that all COM objects must be 'released'. The COM objects from
*	the Direct2D library.
*/
D3Class::~D3Class()
{
    // Clean up the Direct3D stuff
    if (_swapChain) _swapChain->Release();
    if (_swapChain1) _swapChain1->Release();
    if (_device3d) _device3d->Release();
    if (_deviceContext1) _deviceContext1->Release();
    if (_renderTargetView) _renderTargetView->Release();

    if (_vertexShader) _vertexShader->Release();
    if (_vertexLayout) _vertexLayout->Release();
    if (_pVertexBuffer) _pVertexBuffer->Release();

    if (_depthStencilBuffer) _depthStencilBuffer->Release();
    if (_depthStencilState) _depthStencilState->Release();
    if (_depthStencilView) _depthStencilView->Release();

    // Clean up the Direct2D stuff
    if (_d2Factory1) _d2Factory1->Release();
    if (d2d1Context) d2d1Context->Release();
    if (d2d1Device) d2d1Device->Release();
    if (d2d1Bitmap) d2d1Bitmap->Release();

    CoUninitialize();
}



/**
* \brief Initialize the Graphics object and all COM components.
* \details Initialize the necessary resources to use the Direct2D graphics.
*		It includes binding the client's window to the COM.<br/>
* \param windowHandle - HWND - A handle to the client's
* \return bool : true if the Graphics was initialized, else return false.
*/
bool D3Class::Init(HWND windowHandle)
{
    HRESULT hr = S_OK;
    CoInitialize(nullptr);


    //=====================
    //-------------------
    // Acquire the client window size - for rendering targets on this dimension
    RECT rect;
    GetClientRect(windowHandle, &rect);
    D2D1_SIZE_U clientSize = D2D1::SizeU(rect.right, rect.bottom);

    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;
    //-------------------
    //=====================


    //=====================
    //-- CREATE Direct3D Device
    // Creating Direct3D device and context - enables
    // us to use functionalities to be supported in Direct2D
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;


    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
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


    //===-----
    // Creating the Direct3 device depending on the driver type
    //
    _driverType = D3D_DRIVER_TYPE_HARDWARE;
    hr = D3D11CreateDevice(nullptr, _driverType, nullptr, creationFlags, featureLevels, ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION, &device, &_featureLevel, &context);
    if (FAILED(hr)) return false;

    // Obtain a DXGI factory from a device
    IDXGIFactory1* dxgiFactory = nullptr;
    IDXGIDevice* dxgiDevice = nullptr;

    hr = device.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
    if (SUCCEEDED(hr))
    {
        IDXGIAdapter* adapter = nullptr;
        hr = dxgiDevice->GetAdapter(&adapter);
        if (SUCCEEDED(hr)) 
        {
            hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
            adapter->Release();
        }

        dxgiDevice->Release();
    }
    if (FAILED(hr)) return false;
    //-------------------
    //=====================


    //=======================
    //-- CREATE SWAP CHAIN
    IDXGIFactory2* dxgiFactory2 = nullptr;

    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later versions
        hr = device.Get()->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&_device3d));
        if (SUCCEEDED(hr))
        {
            (void)context.Get()->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&_deviceContext1));
        }

        // 3. Defining and describing the swap chain
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

        swapChainDesc.Width = width;
        swapChainDesc.Height = height;
        swapChainDesc.Format =  DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Flags = 0;

        // Create the Swap Chain for the Window Handle
        hr = dxgiFactory2->CreateSwapChainForHwnd(
            device.Get(), 
            windowHandle, 
            &swapChainDesc,
            nullptr, 
            nullptr, 
            &_swapChain1);

        if (SUCCEEDED(hr))
        {
            hr = _swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&_swapChain));
        }

        dxgiFactory2->Release();
    }

    // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
    dxgiFactory->MakeWindowAssociation(windowHandle, DXGI_MWA_NO_ALT_ENTER);
    dxgiFactory->Release();

    if (FAILED(hr))
        return false;


    //=======================
    //-- CREATE RENDER TARGET
    //
    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
        return false;

    hr = device->CreateRenderTargetView(pBackBuffer, nullptr, &_renderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return false;


    //=======================
    //-- Depth Buffers
    //
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

    // Initialize the description of the depth buffer.
    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
    // Set up the description of the depth buffer.
    depthBufferDesc.Width = width;
    depthBufferDesc.Height = height;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;

    // Create the texture for the depth buffer using the filled out description.
    hr = _device3d->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);
    if (FAILED(hr))
        return false;


    //=======================
    //-- Stencil state
    //
    // Initialize the description of the stencil state.
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    // Set up the description of the stencil state.
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing.
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing.
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Create the depth stencil state.
    hr = _device3d->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);
    if (FAILED(hr))
        return false;

    // Set the depth of the stencil state
    _deviceContext1->OMSetDepthStencilState(_depthStencilState, 1);


    //=======================
    //-- Stencil View
    //
    // Initialize the depth stencil view.
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

    // Set up the depth stencil view description.
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // Create the depth stencil view.
    hr = _device3d->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);
    if (FAILED(hr))
        return false;

    // Build the render target view and depth stencil buffer to output render pipeline
    _deviceContext1->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);


    //=======================
    //-- Raster Description
    //
    D3D11_RASTERIZER_DESC rasterDesc;
    // Setup the raster description which will determine how and what polygons will be drawn.
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    hr = _device3d->CreateRasterizerState(&rasterDesc, &_rasterState);
    if (FAILED(hr))
        return false;

    // Set the rasterize state
    _deviceContext1->RSSetState(_rasterState);


    //=======================
    //-- Viewport
    //
    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    _deviceContext1->RSSetViewports(1, &vp);


    //=======================
    //-- Matrix Setup
    //
    float fieldOfView = 0.f;
    float screenAspect = 0.f;

    // Setup the projection matrix.
    fieldOfView = 3.141592654f / 4.0f;
    screenAspect = (float)width / (float)height;

    // Create the projection matrix for 3D rendering.
    _projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);

    // Initialize the world matrix to the identity matrix.
    _worldMatrix = XMMatrixIdentity();

    // Create an orthographic projection matrix for 2D rendering.
    _orthoMatrix = XMMatrixOrthographicLH((float)width, (float)height, SCREEN_NEAR, SCREEN_DEPTH);


    return true;
}


void D3Class::EndDraw(void)
{
    _swapChain->Present(0, 0);
}


ID2D1DeviceContext* D3Class::GetDeviceContext(void)
{
    return d2d1Context;
}



//---------------------------------
//=======================
// DIRECT3D METHODS
//=======================
void D3Class::BeginRender(void) 
{
    // Clear the render target
    _deviceContext1->ClearRenderTargetView(_renderTargetView, Colors::MidnightBlue); 

    // Clear the depth buffer
    _deviceContext1->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


void D3Class::EndRender(void) 
{ 
    _swapChain->Present(0, 0); 
}


ID3D11Device1* D3Class::GetDevice3D(void)
{
    return _device3d;
}


ID3D11DeviceContext1* D3Class::GetDeviceContext3D(void)
{
    return _deviceContext1;
}



//---------------------------------
//=======================
// MATRIX METHODS
//=======================
void D3Class::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
    projectionMatrix = _projectionMatrix;
}


void D3Class::GetWorldMatrix(XMMATRIX& worldMatrix)
{
    worldMatrix = _worldMatrix;
}


void D3Class::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
    orthoMatrix = _orthoMatrix;
}