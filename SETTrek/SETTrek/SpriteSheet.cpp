/*
* PROJECT		: SETTrek
* FILE			: SpriteSheet.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file containing the SpriteSheet class implementation.
*/
#include "SpriteSheet.h"



/**
* \brief
* \details
* \param
* \return
*/
SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics* gfx)
{
	this->gfx = gfx;

	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICFormatConverter *pConverter = NULL;

	// Create the IWICImagingFactory
	// Defines a working place for spawning further tools we can use...
	IWICImagingFactory* pIWICFactory = NULL;
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory
	);

	// Create a Decoder to read file into a WIC Bitmap
	hr = pIWICFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr)) {
		// Read the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr)) {
		// Create a WIC converter
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr)) {
		// Configure the WIC converter
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0f,
			WICBitmapPaletteTypeCustom);
	}
	if (SUCCEEDED(hr)) {
		// Create a Direct2D bitmap from the WIC bitmap.
		gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			&bitmap);
	}

	// CLEAN UP RESOURCES
	if (pIWICFactory) pIWICFactory->Release();
	if (pDecoder) pDecoder->Release();
	if (pSource) pSource->Release();
	if (pConverter) pConverter->Release();
}


/**
* \brief Deconstructor for the SpriteSheet class.
*/
SpriteSheet::~SpriteSheet()
{
	if (bitmap) bitmap->Release();
}


/**
* \brief
*/
void SpriteSheet::Draw(float left, float top)
{
	// Refers to the screen size?
	D2D1_RECT_F destRect = D2D1::RectF(
		left, top,
		bitmap->GetSize().width, bitmap->GetSize().height
	);
	D2D1_RECT_F srcRect = D2D1::RectF(
		left, top,
		bitmap->GetSize().width, bitmap->GetSize().height
	);

	gfx->GetRenderTarget()->DrawBitmap(
		bitmap,
		destRect,
		1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		srcRect
	);
}


void SpriteSheet::Draw(float left, float top, float right, float bottom)
{
	// Refers to the screen size?
	D2D1_RECT_F destRect = D2D1::RectF(
		left, top,
		right, bottom
	);
	// The source rectangle is the screen-size of
	// where the bitmap will be displayed
	D2D1_RECT_F srcRect = D2D1::RectF(
		0, 0,
		1008, 729
	);

	gfx->GetRenderTarget()->DrawBitmap(
		bitmap,
		destRect,
		1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		srcRect
	);
}



/**
* \brief
*/
void SpriteSheet::DrawToTarget(float x1, float y1, float x2, float y2)
{
	D2D1_RECT_F srcRect = D2D1::RectF(
		x1, y1,
		bitmap->GetSize().width, bitmap->GetSize().height
	);
	// Refers to the screen size?
	D2D1_RECT_F destRect = D2D1::RectF(
		x1, y1,
		bitmap->GetSize().width, bitmap->GetSize().height
	);

	gfx->GetRenderTarget()->DrawBitmap(
		bitmap,
		srcRect,
		1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		destRect
	);
}