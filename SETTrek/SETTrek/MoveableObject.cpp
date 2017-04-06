/*
* PROJECT		: SETTrek
* FILE			: MoveableObject.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file implementation for the MoveableObject class.
*/
#include "MoveableObject.h"



//---------------------------------
//=======================
// CONSTRUCTORS
//=======================
/**
* \brief Constructor for the moveable object.
* \details Set the values to a default value.
*/
MoveableObject::MoveableObject()
{
	speedX = 0.0f;
	speedY = 0.0f;
    baseSpeed = 1.0f;
    angle = 0.0f;

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


/**
* \brief Draws the game object to the screen.
* \details Using the Direct2D device context, the game
*	object is drawn to the screen. Four points must be specified
*	for the bitmap to be drawn to the screen. As well, the dimensions
*	of the screen is included to draw the image to the specified screen.
* \param left - float - The left of the rectangle
* \param top - float - The top of the rectangle
* \param right - float - The right of the rectangle
* \param bottom - float - The bottom of the rectangle
* \return void
*/
void MoveableObject::Draw(float left, float top, float right, float bottom)
{
    // Refers to the location of where the bitmap
    // will be drawn, relative to the source (area) rectangle
    // The rectangle needs 4 points to be drawn!
    D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);

    float angle = this->GetAngle();
    D2D1_POINT_2F center = this->GetCenter();

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, center));

    GameObject::Draw(left, top, right, bottom);

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Identity());
}


/**
* \brief Draws the game object to the screen.
* \details Draws the object with an opacity level
* \param left - float - The left of the rectangle
* \param top - float - The top of the rectangle
* \param right - float - The right of the rectangle
* \param bottom - float - The bottom of the rectangle
* \param opacity - float - How transparent the object will be
* \return void
*/
void MoveableObject::Draw(float left, float top, float right, float bottom, float opacity)
{
    D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);

    float angle = this->GetAngle();
    D2D1_POINT_2F center = this->GetCenter();

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, center));

    GameObject::Draw(GetX1(), GetY1(), GetX2(), GetY2());

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Identity());
}


/**
* \brief Draws the game object to the screen.
* \details An additional opacity parameter will adjust the transparency
*   of the object.
*
*   This Draw method takes in two points instead of four points. The right and bottom
*   boundaries are gotten from the bitmap size itself.
*
* \param left - float - The left of the rectangle
* \param top - float - The top of the rectangle
* \param opacity - float - How transparent the object will be
* \see void MoveableObject::Draw(float left, float top, float right, float bottom)
* \see void MoveableObject::Draw(float left, float top, float right, float bottom, float opacity)
* \return void
*/
void MoveableObject::Draw(float left, float top, float opacity)
{
    D2D1_RECT_F destRect = D2D1::RectF(left, top, GameObject::GetBmp()->GetSize().width, GameObject::GetBmp()->GetSize().height);

    float angle = this->GetAngle();
    D2D1_POINT_2F center = this->GetCenter();

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, center));

    GameObject::Draw(GetX1(), GetY1(), GetX2(), GetY2());

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Identity());
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


/**
* \brief Set the speed (x and y) to zero.
* \details Reseting the speed will ensure the object will not move at all.
*/
void MoveableObject::ResetSpeed(void)
{
    speedX = 0.0f;
    speedY = 0.0f;
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
float MoveableObject::GetSpeedX(void) {
	return speedX;
}

/**
* \brief Get the y-speed of the object.
* \return float : Y-speed of the object.
*/
float MoveableObject::GetSpeedY(void) {
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
* \brief Sets if the object is colliding.
* \param colliding - bool - A true/false value for collision
*/
void MoveableObject::SetIsColliding(bool colliding)
{
    isColliding = colliding;
}