/*
* PROJECT		: SETTrek
* FILE			: Level.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"



/**
* \class Level
* \brief The Level is an abstract class that encapsulates the attributes of a game level.
*/
class Level
{
protected:
	static Graphics* gfx;		//!< Reference to the Graphics object

public:

	static void Init(Graphics * graphics);

	virtual void Load(void) = 0;		// For loading assets for the game level
	virtual void Unload(void) = 0;		// For unloading assets from the game level
	virtual void Update(void) = 0;		// For updating the game level
	virtual void Render(void) = 0;		// For rendering the game level
};