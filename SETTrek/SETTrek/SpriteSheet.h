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

	LPCWSTR file;			//!< The file of the resource

public:

	/*-Constructor-*/
	SpriteSheet(LPCWSTR filename, Graphics* gfx, ID2D1Bitmap1** bmp);

	/*-Destructor-*/
	~SpriteSheet();

	/*-Accessors-*/
	LPCWSTR GetFile(void) const;

	/*-Mutators-*/
	void SetFile(LPCWSTR fileName);
};