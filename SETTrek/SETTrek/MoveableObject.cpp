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
    angle = 0.0f;
}


MoveableObject::MoveableObject(float xSpeed, float ySpeed, Graphics* graphics, D2D1_RECT_F area)
	: GameObject(graphics, area)
{
	speedX = xSpeed;
	speedY = ySpeed;
    angle = 0.0f;
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
// CALCULATIONS
//=======================
void MoveableObject::CalculateSpeed(float deltaX, float deltaY)
{
    // distance = sqr (deltaX^2 + deltaY^2);
    float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
    float overallX = 0.0f;
    float overallY = 0.0f;
    if (distance != 0)
    {
        overallX = deltaX * kConstSpeed / distance;
        overallY = deltaY * kConstSpeed / distance;

        SetSpeedX(overallX);
        SetSpeedY(overallY);
    }
}


void MoveableObject::CalculateAngle(float opposite, float ajacent)
{
    float a = atan2f(opposite, ajacent) * 180.f / PI;

    SetAngle(a);
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
float MoveableObject::GetCenterX(void) 
{
	return (GameObject::GetX1() + GameObject::GetX2()) / 2;
}
float MoveableObject::GetCenterY(void) 
{
	return (GameObject::GetY1() + GameObject::GetY2()) / 2;
}
float MoveableObject::GetAngle(void)
{
    return angle;
}


void MoveableObject::SetSpeedX(float x) {
	speedX = x;
}
void MoveableObject::SetSpeedY(float y) {
	speedY = y;
}
void MoveableObject::SetAngle(float a)
{
    angle = a;
}