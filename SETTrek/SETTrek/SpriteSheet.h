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
* \brief The spritesheet loads bitmap resources from file.
*/
class SpriteSheet
{
private:


public:

	/*-Constructor-*/
	SpriteSheet(LPCWSTR filename, Graphics* gfx);
	SpriteSheet(LPCWSTR filename, Graphics* gfx, ID2D1Bitmap** bmp);

	/*-Destructor-*/
	~SpriteSheet();
};