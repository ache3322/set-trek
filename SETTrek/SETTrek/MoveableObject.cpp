/*
* PROJECT		: SETTrek
* FILE			: GameObject.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file implementation for the GameObject class.
*/
#include "MoveableObject.h"



//---------------------------------
//=======================
// CONSTRUCTORS
//=======================
/**
* \brief Constructor for the game object.
* \details Set the values to a default value.
* \param graphics - Graphics* - A reference to the graphics object
* \param area - D2D1_RECT_F - The dimensions of the screen
* \return None
*/
MoveableObject::MoveableObject(Graphics* graphics, D2D1_RECT_F area)
	: GameObject(graphics, area)
{
	speedX = 0.0f;
	speedY = 0.0f;
}


MoveableObject::MoveableObject(float xSpeed, float ySpeed, Graphics* graphics, D2D1_RECT_F area)
	: GameObject(graphics, area)
{
	speedX = xSpeed;
	speedY = ySpeed;
}



//---------------------------------
//=======================
// DECONSTRUCTORS
//=======================
/**
* \brief Deconstructor for the object.
* \details Any COM objects that are used within the object
*	must be released.
* \param None
* \return None
*/
MoveableObject::~MoveableObject()
{
}



//---------------------------------
//=======================
// DECONSTRUCTORS
//=======================
void MoveableObject::CalculateSpeed(float deltaX, float deltaY)
{
    // distance = sqr (deltaX^2 + deltaY^2);
    float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
    float overallX = deltaX * kConstSpeed / distance;
    float overallY = deltaY * kConstSpeed / distance;

    SetSpeedX(overallX);
    SetSpeedY(overallY);
}



//---------------------------------
//=======================
// MUTATORS / SETTERS
//=======================
//-------------------------------------------------
float MoveableObject::GetSpeedX(void) const {
	return speedX;
}
float MoveableObject::GetSpeedY(void) const {
	return speedY;
}

void MoveableObject::SetSpeedX(float x) {
	speedX = x;
}
void MoveableObject::SetSpeedY(float y) {
	speedY = y;
}