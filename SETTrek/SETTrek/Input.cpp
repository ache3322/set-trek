/*
* PROJECT		: SETTrek
* FILE			: Input.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file containing the class defintion for a Input class.
*/
#include "Input.h"



float Input::I_leftMouseX;
float Input::I_leftMouseY;
float Input::I_rightMouseX;
float Input::I_rightMouseY;
unsigned int Input::I_keyValue;
volatile bool Input::isLeftClick;
volatile bool Input::isRightClick;
volatile bool Input::isKeyDown;


/**
* \brief This initialize the static variables to a default value
* \param None
* \return None
*/
void Input::InitInput(void)
{
    I_leftMouseX = 0.f;
    I_leftMouseY = 0.f;
    I_rightMouseX = 0.f;
    I_rightMouseY = 0.f;
    I_keyValue = 0x00;

    // Boolean for left and right click events
    isLeftClick = false;
    isRightClick = false;
    isKeyDown = false;
}