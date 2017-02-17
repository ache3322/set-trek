/*
* PROJECT		: SETTrek
* FILE			: EffectManager.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/16
* DESCRIPTION	: The CPP file containing the class implementation for the EffectManager.
*/
#include "EffectManager.h"



/**
* \brief Creating a chroma key effect.
* \details Creating a chroma key effect. A bitmap source must
*	be passed in to create the effect out of it. The chroma effect
*	will look for a specified color and will "remove" it.
* \param gfx - Graphics* - A reference to the Graphics object
* \param bmp1 - ID2D1Bitmap* - The effects being applied to the bitmap
*/
ID2D1Effect* EffectManager::CreateChroma(Graphics* gfx, ID2D1Bitmap* bmp1)
{
	ID2D1Effect* chroma = NULL;

	// Create the chromakey effect
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1ChromaKey, &chroma);

	// The bitmap that will be chromakeyed
	chroma->SetInput(0, bmp1);
	// RGB Channel - R, G, B, A
	HRESULT hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 1.0f, 0.0f));
	// TODO: Pass in float to control tolerance?
	hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.15f);
	hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, 0);
	hr = chroma->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, 1);

	return chroma;
}


/**
* \brief Creating a composite effect.
* \details The composite effect needs to bitmap sources. Both bitmaps will
*	be composited over each other.
* \param gfx - Graphics* - A reference to the Graphics object
* \param bmp1 - ID2D1Bitmap* - A bitmap being composited
* \param bmp2 - ID2D1Bitmap* - The second bitmap composited over the first bitmap
*/
ID2D1Effect* EffectManager::CreateComposite(Graphics* gfx, ID2D1Bitmap* bmp1, ID2D1Bitmap* bmp2)
{
	ID2D1Effect* composite = NULL;

	// Create the chromakey effect
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1Composite, &composite);

	composite->SetInput(0, bmp1);
	composite->SetInput(1, bmp2);

	return composite;
}



/**
* \brief Convert a Direct2D effect to a Direct2D bitmap.
* Credit:  MrSmith - http://stackoverflow.com/questions/31118397/direct2d-convert-id2d1image-to-id2d1bitmap
* \param effect - ID2D1Effect* - The effect being transferred to the bitmap
* \param size - D2D1_SIZE_U - The size of the bitmap or render target
*/
ID2D1Bitmap1* EffectManager::ConvertToBitmap(Graphics* gfx, ID2D1Effect* effect, D2D1_SIZE_U size)
{
	ComPtr<ID2D1Image> oldTarget;
	ID2D1Bitmap1* newBitmap = NULL;

	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	gfx->GetDeviceContext()->CreateBitmap(size, nullptr, 0, bitmapProperties, &newBitmap);

	// Here is the part of trying to convert the effects to a bitmap...
	// The process for conversion is SetTarget and GetTarget

	// First, begin drawing 
	gfx->BeginDraw();

	// Retrieve/save the target that the DeviceContext is pointing at...
	// Basically this is the screen that was rendered when the Graphics was initialized
	gfx->GetDeviceContext()->GetTarget(&oldTarget);
	//---------------
	// This section is where we convert the effects to bitmap
	// First we set target (focus) on that bitmap
	gfx->GetDeviceContext()->SetTarget(newBitmap);
	// Then we draw the Effects ontop of the bitmap
	gfx->GetDeviceContext()->DrawImage(effect, D2D1_INTERPOLATION_MODE_LINEAR);
	//---------------
	// IMPORTANT: Set the old target back
	gfx->GetDeviceContext()->SetTarget(oldTarget.Get());

	// Last, end Draw
	gfx->EndDraw();

	// Return the bitmap with the applied effects!
	return newBitmap;
}


/**
* \brief Convert a Direct2D image to a Direct2D bitmap.
* Credit: MrSmith - http://stackoverflow.com/questions/31118397/direct2d-convert-id2d1image-to-id2d1bitmap
* \param effect - ID2D1Image* - The image that is converted to a bitmap
* \param size - D2D1_SIZE_U - The size of the bitmap or render target
*/
ID2D1Bitmap1* EffectManager::ConvertToBitmap(Graphics* gfx, ID2D1Image* image, D2D1_SIZE_U size)
{
	ComPtr<ID2D1Image> oldTarget;
	ID2D1Bitmap1* newBitmap = NULL;

	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	gfx->GetDeviceContext()->CreateBitmap(size, nullptr, 0, bitmapProperties, &newBitmap);

	// Here is the part of trying to convert the effects to a bitmap...
	// The process for conversion is SetTarget and GetTarget

	// First, begin drawing 
	gfx->BeginDraw();

	// Retrieve/save the target that the DeviceContext is pointing at...
	// Basically this is the screen that was rendered when the Graphics was initialized
	gfx->GetDeviceContext()->GetTarget(&oldTarget);
	//---------------
	// This section is where we convert the effects to bitmap
	// First we set target (focus) on that bitmap
	gfx->GetDeviceContext()->SetTarget(newBitmap);
	// Then we draw the Effects ontop of the bitmap
	gfx->GetDeviceContext()->DrawImage(image, D2D1_INTERPOLATION_MODE_LINEAR);
	//---------------
	// IMPORTANT: Set the old target back
	gfx->GetDeviceContext()->SetTarget(oldTarget.Get());

	// Last, end Draw
	gfx->EndDraw();

	return newBitmap;
}