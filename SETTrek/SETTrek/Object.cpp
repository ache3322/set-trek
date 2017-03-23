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


void Object::Initialize(Graphics* graphics, D2D1_RECT_F screen)
{
    gfx = graphics;
    renderArea = screen;
}