/*
* PROJECT		: SETTrek
* FILE			: EffectManager.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/16
* DESCRIPTION	: The header file containing the class definition for the EffectManager.
*/
#pragma once
#include "Graphics.h"



/**
* \class EffectManager
* \brief The EffectManager class basically applies Direct2D effects to bitmap images.
* \details The class allows for the creation and application of Direct2D Effects to be applied
*	to Direct2D Bitmaps. Each Effect takes in one or more Bitmap sources.
*/
class EffectManager
{
private:

	static Graphics* gfx;

public:

	static void Init(Graphics* graphics);

	static ID2D1Effect* CreateChroma(ID2D1Bitmap* bmp1);
	static ID2D1Effect* CreateChroma(ID2D1Bitmap* bmp1, float tolerance);
	static ID2D1Effect* CreateChroma(ID2D1Bitmap* bmp1, float tolerance, int isFeather);
	static ID2D1Effect* CreateChroma(ID2D1Bitmap* bmp1, D2D1_VECTOR_3F color, float tolerance);
	static ID2D1Effect* CreateChroma(ID2D1Bitmap* bmp1, float r, float g, float b, float tolerance);
	static ID2D1Effect* CreateComposite(ID2D1Bitmap* bmp1, ID2D1Bitmap* bmp2);


	//-Conversion Methods-
	static ID2D1Bitmap1* ConvertToBitmap(ID2D1Effect* effect, D2D1_SIZE_U size);
	static ID2D1Bitmap1* ConvertToBitmap(ID2D1Image* image, D2D1_SIZE_U size);
};