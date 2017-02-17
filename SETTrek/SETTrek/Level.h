/*
* PROJECT		: SETTrek
* FILE			: Level.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	: The header file containing an abstract definition of the Level interface.
*/
#pragma once
#include "Graphics.h"



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

	virtual void Load(D2D1_RECT_F size) = 0;	// For loading assets for the game level
	virtual void Unload(void) = 0;				// For unloading assets from the game level
	virtual void Update(void) = 0;				// For updating the game level
	virtual void Render(void) = 0;				// For rendering the game level
};