/*
* PROJECT		: SETTrek
* FILE			: SpriteSheet.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class definition for the spritesheet.
*/
#pragma once
#include <Wincodec.h>
#include "Graphics.h"



/**
* \class SpriteSheet
* \brief
*/
class SpriteSheet
{
private:

	Graphics* gfx;			//!< Reference to the Graphics class
	ID2D1Bitmap* bitmap;	//!< Holds the loaded Bitmap file

public:

	/*-Constructor-*/
	SpriteSheet(LPCWSTR filename, Graphics* gfx);
	SpriteSheet(LPCWSTR filename, Graphics* gfx, ID2D1Bitmap** bmp);

	/*-Destructor-*/
	~SpriteSheet();

	/*-Other Methods-*/
	void Draw(float left, float top, float right, float bottom);
	void Draw(float left, float top, float right, float bottom, D2D1_RECT_F windowSize);
};