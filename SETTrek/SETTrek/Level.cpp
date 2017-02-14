/*
* PROJECT		: SETTrek
* FILE			: Level.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#include "Level.h"



//-STATIC VARIABLE INSTANCE
Graphics* Level::gfx;



/**
* \brief Ensures the Level has access to the Graphics object.
* \param graphics - Graphics* - A reference to the Graphics object.
*/
void Level::Init(Graphics* graphics)
{
	gfx = graphics;
}