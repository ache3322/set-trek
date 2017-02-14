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
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;
}

/**
* \brief Destructor for Graphics class
* \details Note that all COM objects must be 'released'. The COM objects are contained
*		in the d2d1 header file.
*/
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}


/**
* \brief Initialize the Graphics object and all COM components.
* \details Initialize the necessary resources to use the Direct2D graphics.
*		It includes binding the client's window to the COM.
* \param windowHandle - HWND - A handle to the client's 
* \return bool : If Graphics is able to initialize.
*/
bool Graphics::Init(HWND windowHandle)
{
	CoInitialize(nullptr);

	// Create D2D1 object to be used to create D2D1 resources.
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size

	// Create a render target to render window
	// HwndRenderTargetProperties:
	//    HWND - target issues output from its drawing commands
	//    pixelSize - sizeo of the redner target, in pixels
	//		> We use the rectangle size of the client window
	//    D2D1_PRESENT_OPTIONS - specifies whether target retains frame after it is presented
	//		> rendertarget is the render targe
	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);
	if (res != S_OK) {
		return false;
	}
	
	res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) {
		return false;
	}
	return true;
}


/**
* \brief Get the render target.
* \return ID2D1RenderTarget* - A reference to the render target.
*/
ID2D1RenderTarget* Graphics::GetRenderTarget(void)
{
	return rendertarget;
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
	rendertarget->Clear(D2D1::ColorF(r, g, b));
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
*/
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	// Render the shape on the target...
	// Ellipse takes a position (x,y); width; height; brush; and brush stroke
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);	

}


void Graphics::DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	// Render the shape on the target...
	rendertarget->DrawRectangle(D2D1::Rect(left, top, right, bottom), brush, 3.0f);
}