/*
* PROJECT		: SETTrek
* FILE			: Level.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	: The CPP file for the Level interface. This particular file
*	includes the reference to a Graphics object.
*/
#include "Level.h"



//-STATIC VARIABLE INSTANCE
Graphics* Level::gfx;
D2D1_RECT_F Level::screenSize;
Grid* Level::grid;
Level::GameMode Level::mode = spaceMode;


/**
* \brief Ensures the Level has access to the Graphics object.
* \param graphics - Graphics* - A reference to the Graphics object.
*/
void Level::Init(Graphics* graphics, D2D1_RECT_F screen)
{
	gfx = graphics;
    screenSize = screen;

    grid = new Grid(screenSize.right, screenSize.bottom);
}


/**
* \brief Reinitialize the grid size.
*/
void Level::ReInitGrid(void)
{
    if (grid) 
    {
        delete grid;
        grid = nullptr;
    }

    if (!grid)
    {
        grid = new Grid(screenSize.right, screenSize.bottom);
    }
}