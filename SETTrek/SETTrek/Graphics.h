/*
* PROJECT		: SETTrek
* FILE			: Graphics.h
* PROGRAMMER	:
* DATE			: 2017/01/25
* DESCRIPTION	: The header file containing the class definition for the Graphics.
*/
#pragma once
#include <Windows.h>
#include <d2d1.h>



/**
* \class Graphics
* \brief
*/
class Graphics
{
private:

	ID2D1Factory* factory; //The factory allows us to create many other types of D2D resources
	ID2D1HwndRenderTarget* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!
	
public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	ID2D1RenderTarget* GetRenderTarget(void);

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a);
};
