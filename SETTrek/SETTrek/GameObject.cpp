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
	chroma = NULL;

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
	if (chroma) chroma->Release();
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
	// The bitmap asset will be loaded
	SpriteSheet sprite(fileName, gfx, &bitmap);

	//ComPtr<ID2D1Effect> chromaKeyEffect;
	gfx->GetDeviceContext()->CreateEffect(
		CLSID_D2D1ChromaKey, &chroma
	);


	// RGB Channel - R, G, B, A
	D2D1_VECTOR_3F color = { 0.0f, 1.0f, 0.0f };

	chroma->SetInput(0, bitmap);
	HRESULT hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_COLOR, color);
	hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.1f);
	hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, 0);
	hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, 0);
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

	//ComPtr<ID2D1Image> image;
	//chroma->GetOutput(&image);

	gfx->GetDeviceContext()->DrawBitmap(
		bitmap,
		destRect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		renderArea);

/*	gfx->GetDeviceContext()->DrawImage(
		image.Get(),
		D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR)*/;



	//gfx->GetDeviceContext()->DrawImage(
	//	chroma,
	//	D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
	//gfx->GetDeviceContext()->DrawBitmap(
	//	chroma,
	//	destRect,
	//	1.0f,
	//	D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
	//	renderArea);
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