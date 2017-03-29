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
    //-------------------
    // Creating Direct3D device and context - enables
    // us to use functionalities to be supported in Direct2D
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    //ComPtr<IDXGIDevice> dxgiDevice;


    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

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
    _driverType = driverTypes[0];
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

    context->OMSetRenderTargets(1, &_renderTargetView, nullptr);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    context->RSSetViewports(1, &vp);


    //=======================
    //-- Compile the VERTEX
    //


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


ID3D11DeviceContext* D3Class::GetDeviceContext3D(void)
{
    return _deviceContext1;
}