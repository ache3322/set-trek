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

	/*-Destructor-*/
	~SpriteSheet();

	/*-Other Methods-*/
	void DrawToTarget(void);
};