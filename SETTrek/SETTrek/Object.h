/*
* PROJECT		: SETTrek
* FILE			: Object.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/03/23
* DESCRIPTION	: The header file containing the class defintion for a Object.
*       The Object class provides an interface for the entire family of GameObjects.
*       This includes the usage of a static Graphics object and screen area.
*/
#pragma once
#include <Wincodec.h>
#include "Graphics.h"
#include "SpriteSheet.h"



/**
* \class Object
* \brief The Object is an abstract class that allows for access to the Graphics.
*/
class Object
{
protected:
    static Graphics* gfx;		    //!< Reference to the Graphics object
    static D2D1_RECT_F renderArea;	//!< The rectangle area/size of where the object will be drawn

public:

    static void Initialize(Graphics* graphics, D2D1_RECT_F screen);

    virtual void Init(LPCWSTR fileName) = 0;            // For loading assets / resources
    virtual Graphics* GetGfx(void) = 0;
};