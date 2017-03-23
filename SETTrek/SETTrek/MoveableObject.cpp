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
MoveableObject::MoveableObject()
{
	speedX = 0.0f;
	speedY = 0.0f;
    baseSpeed = 1.0f;
    angle = 0.0f;
    
    health = kDefaultHealth;
}

MoveableObject::MoveableObject(float xSpeed, float ySpeed)
{
	speedX = xSpeed;
	speedY = ySpeed;
    baseSpeed = 1.0f;
    angle = 0.0f;

    health = kDefaultHealth;
}

MoveableObject::MoveableObject(float xSpeed, float ySpeed, float bSpeed)
{
    speedX = xSpeed;
    speedY = ySpeed;
    baseSpeed = bSpeed;
    angle = 0.0f;

    health = kDefaultHealth;
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
//========================
// DIRECTX GRAPHICS STUFF
//========================
/**
* \brief Initialization of the game object.
* \details The initialization process will load bitmap resources from file.
* \param fileName - LPCWSTR - The filename to the resource
* \return void
*/
void MoveableObject::Init(LPCWSTR fileName)
{
    // Initialization of the asset - getting resources from file
    // The bitmap asset will be loaded to a temporary bitmap
    GameObject::Init(fileName);
}


/**
* \brief Get the static reference to the Graphics.
* \param None
* \return Graphics* : The graphics.
*/
Graphics* MoveableObject::GetGfx(void)
{
    return gfx;
}



//---------------------------------
//=======================
// CALCULATIONS
//=======================
/**
* \brief Calculates the optimal speed path.
* \details Uses the calculation to retrieve the hypotenuse.
* \param deltaX - float - The difference in the x2 and x1
* \param deltaY - float - The difference in the y2 and y1
* \return None
*/
void MoveableObject::CalculateSpeed(float deltaX, float deltaY)
{
    // distance = sqr (deltaX^2 + deltaY^2);
    float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
    float overallX = 0.0f;
    float overallY = 0.0f;
    if (distance != 0)
    {
        overallX = deltaX * baseSpeed / distance;
        overallY = deltaY * baseSpeed / distance;

        SetSpeedX(overallX);
        SetSpeedY(overallY);
    }
}

/**
* \brief Calculates the optimal speed path. This method takes a
*   percent for how fast the object will move.
* \details Uses the calculation to retrieve the hypotenuse.
*   distance = sqr (deltaX^2 + deltaY^2)
* \param deltaX - float - The difference in the x2 and x1
* \param deltaY - float - The difference in the y2 and y1
* \param percent - float - The percent of the speed
* \return None
*/
void MoveableObject::CalculateSpeed(float deltaX, float deltaY, float percent)
{
	float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	float newSpeedX = 0.0f;
	float newSpeedY = 0.0f;
	if (distance != 0)
	{
		newSpeedX = deltaX * baseSpeed / distance;
		newSpeedY = deltaY * baseSpeed / distance;

		newSpeedX = newSpeedX + (newSpeedX * percent);
		newSpeedY = newSpeedY + (newSpeedY * percent);

		SetSpeedX(newSpeedX);
		SetSpeedY(newSpeedY);
	}
}


void MoveableObject::CalculateAngle(float opposite, float ajacent)
{
    float a = atan2f(opposite, ajacent) * 180.f / PI;

    SetAngle(a);
}


//---------------------------------
//=======================
// GETTERS
//=======================
//-------------------------------------------------
float MoveableObject::GetSpeedX(void) const {
	return speedX;
}
float MoveableObject::GetSpeedY(void) const {
	return speedY;
}
float MoveableObject::GetBaseSpeed(void) 
{
    return baseSpeed;
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
float MoveableObject::GetHealth(void)
{
    return health;
}


//---------------------------------
//=======================
// SETTERS
//=======================
void MoveableObject::SetSpeedX(float x) {
	speedX = x;
}
void MoveableObject::SetSpeedY(float y) {
	speedY = y;
}
void MoveableObject::SetBaseSpeed(float s)
{
    baseSpeed = s;
}
void MoveableObject::SetAngle(float a)
{
    angle = a;
}
void MoveableObject::SetHealth(float h)
{
    health = h;
}