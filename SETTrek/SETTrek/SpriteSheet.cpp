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