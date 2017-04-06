/*
* PROJECT		: SETTrek
* FILE			: Input.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class defintion for a Input class.
*       The Input class takes input from the user of the program
*/
#pragma once




/**
* \class Input
* \brief This is the Input class.
* \details The Input class stores and takes the user's input.
*   This class and it's static variables can be accessed throughout
*   the entire application.
*/
class Input
{
public:

    static float I_leftMouseX;
    static float I_leftMouseY;
    static float I_rightMouseX;
    static float I_rightMouseY;

    static volatile bool isLeftClick;
    static volatile bool isRightClick;

    static void InitInput(void);
};