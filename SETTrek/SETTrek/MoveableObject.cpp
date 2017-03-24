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
* \brief Constructor for the moveable object.
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
    isColliding = false;
}

/**
* \brief Constructor for the moveable object. Takes
*       in two parameters for the speeds.
* \param xSpeed - float - The x-direction speed
* \param ySpeed - float - The y-direction speed
* \return None
*/
MoveableObject::MoveableObject(float xSpeed, float ySpeed)
{
	speedX = xSpeed;
	speedY = ySpeed;
    baseSpeed = 1.0f;
    angle = 0.0f;

    health = kDefaultHealth;
    isColliding = false;
}

/**
* \brief Constructor for the moveable object. Takes
*       in three parameters for the speeds.
* \param xSpeed - float - The x-direction speed
* \param ySpeed - float - The y-direction speed
* \param bSpeed - float - The base speed for the object.
* \return None
*/
MoveableObject::MoveableObject(float xSpeed, float ySpeed, float bSpeed)
{
    speedX = xSpeed;
    speedY = ySpeed;
    baseSpeed = bSpeed;
    angle = 0.0f;

    health = kDefaultHealth;
    isColliding = false;
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


/**
* \brief Calculates the angle of rotation.
* \details The angle of rotation is determined by the opposite
*       and adjacent sides of a triangle. The arc tan is calculated
*       and converted to degrees.
* \param opposite - float - The opposite side (or y-side of a triangle)
* \param adjacent - float - The adjacent side (or x-side of a triangle
* \return None
*/
void MoveableObject::CalculateAngle(float opposite, float adjacent)
{
    float a = atan2f(opposite, adjacent) * 180.f / PI;

    SetAngle(a);
}


//---------------------------------
//=======================
// GETTERS
//=======================
//-------------------------------------------------
/**
* \brief Get the x-speed of the object.
* \return float : X-speed of the object.
*/
float MoveableObject::GetSpeedX(void) const {
	return speedX;
}

/**
* \brief Get the y-speed of the object.
* \return float : Y-speed of the object.
*/
float MoveableObject::GetSpeedY(void) const {
	return speedY;
}

/**
* \brief Get the base-speed of the object.
* \return float : Base-speed of the object.
*/
float MoveableObject::GetBaseSpeed(void) 
{
    return baseSpeed;
}

/**
* \brief Get the center-x position
* \return float : center-x position.
*/
float MoveableObject::GetCenterX(void) 
{
	return (GameObject::GetX1() + GameObject::GetX2()) / 2;
}

/**
* \brief Get the center-y position
* \return float : center-y position.
*/
float MoveableObject::GetCenterY(void) 
{
	return (GameObject::GetY1() + GameObject::GetY2()) / 2;
}

/**
* \brief Get the angle of rotation.
* \return float : the angle
*/
float MoveableObject::GetAngle(void)
{
    return angle;
}

/**
* \brief Get the health
* \return float : health of the object.
*/
float MoveableObject::GetHealth(void)
{
    return health;
}

/**
* \brief Gets a boolean of if the object is colliding with something.
* \return bool : true if collision detected; false if no collision
*/
bool MoveableObject::IsColliding(void)
{
    return isColliding;
}


//---------------------------------
//=======================
// SETTERS
//=======================
/**
* \brief Sets the x-speed of the object.
* \param x - float - The new x-speed.
*/
void MoveableObject::SetSpeedX(float x) {
	speedX = x;
}

/**
* \brief Sets the y-speed of the object.
* \param y - float - The new y-speed.
*/
void MoveableObject::SetSpeedY(float y) {
	speedY = y;
}

/**
* \brief Sets the base-speed of the object.
* \param s - float - The new base-speed.
*/
void MoveableObject::SetBaseSpeed(float s)
{
    baseSpeed = s;
}

/**
* \brief Sets the angle of rotation of the object.
* \param a - float - The new angle
*/
void MoveableObject::SetAngle(float a)
{
    angle = a;
}

/**
* \brief Sets the health of the object.
* \param h - float - The health
*/
void MoveableObject::SetHealth(float h)
{
    health = h;
}

/**
* \brief Sets if the object is colliding.
* \param colliding - bool - A true/false value for collision
*/
void MoveableObject::SetIsColliding(bool colliding)
{
    isColliding = colliding;
}