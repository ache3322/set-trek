/*
* PROJECT		: SETTrek
* FILE			: Object.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/03/23
* DESCRIPTION	: The CPP file implementation for the Object class.
*/
#include "Object.h"


//-STATIC VARIABLE INSTANCE
Graphics* Object::gfx;
D2D1_RECT_F Object::renderArea;


/**
* \brief Initialize the base 'Game' object.
* \details This object allows for the usage of a static Graphics reference
*   and the size/area of the client area.
* \param graphics - Graphics* - A reference to the Graphics instance
* \param screen - D2D1_RECT_F - The area of the screen
*/
void Object::Initialize(Graphics* graphics, D2D1_RECT_F screen)
{
    gfx = graphics;
    renderArea = screen;
}