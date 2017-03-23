/*
* PROJECT		: SETTrek
* FILE			: SpriteSheet.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file containing the SpriteSheet class implementation.
*/
#include "SpriteSheet.h"



/**
* \brief Loading a bitmap resource (from file) to memory.
* \param[in] filename - LPCWSTR - The file name / path to the asset
* \param gfx - Graphics* - Creating render target area for drawing bitmap
* \param[out] bmp - ID2D1Bitmap** - Where to save the bitmap resource
*/
SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics* gfx, ID2D1Bitmap1** bmp)
{
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

	// Create a Decoder to read file into a IWIC Bitmap
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
		gfx->GetDeviceContext()->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			bmp);
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
}