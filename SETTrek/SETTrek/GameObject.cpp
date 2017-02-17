/*
* PROJECT		: SETTrek
* FILE			: GameObject.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file implementation for the GameObject class.
*/
#include "GameObject.h"



/**
* \brief
* \details
* \param
* \return
*/
GameObject::GameObject(Graphics* graphics, D2D1_RECT_F area)
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;

	bitmap = NULL;
	// Set reference to the Graphics object
	gfx = graphics;
	// Set the area to render the GameObject
	renderArea = area;
}


/**
* \brief
* \details
* \param
* \return
*/
GameObject::~GameObject()
{
	if (bitmap) bitmap->Release();
}


/**
* \brief
* \details
* \param
* \return
*/
void GameObject::Init(LPCWSTR fileName)
{
	// Initialization of the asset - getting resources from file
	// The bitmap asset will be loaded to a temporary bitmap
	SpriteSheet sprite(fileName, gfx, &bitmap);
}


/**
* \brief
* \details
* \param left - float
* \param top - float 
* \param right - float 
* \param bottom - float
* \return
*/
void GameObject::Draw(float left, float top, float right, float bottom)
{
	// Refers to the location of where the bitmap
	// will be drawn, relative to the source (area) rectangle
	// The rectangle needs 4 points to be drawn!
	D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);

	gfx->GetDeviceContext()->DrawBitmap(
		bitmap,
		destRect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		renderArea);
}



ID2D1Bitmap* GameObject::GetBitmap(void)
{
	return bitmap;
}
D2D1_SIZE_U GameObject::GetBitmapPixelSize(void)
{
	return bitmap->GetPixelSize();
}
float GameObject::GetX1(void)
{
	return x1;
}
float GameObject::GetY1(void)
{
	return y1;
}
float GameObject::GetX2(void)
{
	return x2;
}
float GameObject::GetY2(void)
{
	return y2;
}


void GameObject::SetBitmap(ID2D1Bitmap* bmp)
{
	if (bitmap)
	{
		bitmap->Release();
		bitmap = nullptr;
	}
	bitmap = bmp;
}
void GameObject::SetX1(float x)
{
	x1 = x;
}
void GameObject::SetY1(float y)
{
	y1 = y;
}
void GameObject::SetX2(float x)
{
	x2 = x;
}
void GameObject::SetY2(float y)
{
	y2 = y;
}