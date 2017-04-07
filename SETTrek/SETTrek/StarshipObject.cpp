/*
* PROJECT		: SETTrek
* FILE			: StarshipObject.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file implementation for the StarshipObject class.
*/
#include "StarshipObject.h"



//---------------------------------
//=======================
// CONSTRUCTORS
//=======================
/**
* \brief Constructor for the Starship object.
* \details Set the values to a default value.
*/
StarshipObject::StarshipObject()
{
    health = kDefaultHealth;
    laserX = 0.0f;
    laserY = 0.0f;
    laserSpeedX = 0.0f;
    laserSpeedY = 0.0f;

    laserAmmo = kDefaultAmmoLimit;

    isMoving = true;
    isColliding = false;
    isDead = false;
    isFireLaser = false;
}

/**
* \brief Constructor for the starship object. Takes
*       in two parameters for the speeds. Calls upon the MoveableObject constructor.
* \param xSpeed - float - The x-direction speed
* \param ySpeed - float - The y-direction speed
* \return None
*/
StarshipObject::StarshipObject(float x, float y)
    : MoveableObject(x, y)
{
    health = kDefaultHealth;
    laserX = 0.0f;
    laserY = 0.0f;
    laserSpeedX = 0.0f;
    laserSpeedY = 0.0f;

    laserAmmo = kDefaultAmmoLimit;

    isMoving = true;
    isColliding = false;
    isDead = false;
    isFireLaser = false;
}

/**
* \brief Constructor for the starship object. Takes
*       in two parameters for the speeds. Calls upon the MoveableObject constructor.
* \param xSpeed - float - The x-direction speed
* \param ySpeed - float - The y-direction speed
* \param baseSpeed - float - The base speed for the object.
* \return None
*/
StarshipObject::StarshipObject(float xSpeed, float ySpeed, float baseSpeed)
    : MoveableObject(xSpeed, ySpeed, baseSpeed)
{
    health = kDefaultHealth;
    laserX = 0.0f;
    laserY = 0.0f;
    laserSpeedX = 0.0f;
    laserSpeedY = 0.0f;

    laserAmmo = kDefaultAmmoLimit;

    isMoving = true;
    isColliding = false;
    isDead = false;
    isFireLaser = false;
}

/**
* \brief Constructor for the starship object. Takes
*       in two parameters for the speeds. Calls upon the MoveableObject constructor.
* \param xSpeed - float - The x-direction speed
* \param ySpeed - float - The y-direction speed
* \param baseSpeed - float - The base speed for the object.
* \param health - float - The health of the starship.
* \return None
*/
StarshipObject::StarshipObject(float xSpeed, float ySpeed, float baseSpeed, float health)
    : MoveableObject(xSpeed, ySpeed, baseSpeed)
{
    this->health = health;
    laserX = 0.0f;
    laserY = 0.0f;
    laserSpeedX = 0.0f;
    laserSpeedY = 0.0f;

    laserAmmo = kDefaultAmmoLimit;

    isMoving = true;
    isColliding = false;
    isDead = false;
    isFireLaser = false;
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
StarshipObject::~StarshipObject(void)
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
void StarshipObject::Init(LPCWSTR fileName)
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
Graphics* StarshipObject::GetGfx(void)
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
void StarshipObject::Draw(float left, float top, float right, float bottom)
{
    // Refers to the location of where the bitmap
    // will be drawn, relative to the source (area) rectangle
    // The rectangle needs 4 points to be drawn!
    MoveableObject::Draw(left, top, right, bottom);
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
void StarshipObject::Draw(float left, float top, float right, float bottom, float opacity)
{
    MoveableObject::Draw(left, top, right, bottom);
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
* \see void StarshipObject::Draw(float left, float top, float right, float bottom)
* \see void StarshipObject::Draw(float left, float top, float right, float bottom, float opacity)
* \return void
*/
void StarshipObject::Draw(float left, float top, float opacity)
{
    MoveableObject::Draw(left, top, MoveableObject::GetX2(), MoveableObject::GetY2());
}


/**
*
*
*
*/
void StarshipObject::CalculateLaserSpeed(float deltaX, float deltaY, float multiplier)
{
    float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
    float overallX = 0.0f;
    float overallY = 0.0f;

    if (distance != 0)
    {
        // Calculation for the optimal x and y speed position
        overallX = deltaX * 7.f / distance;
        overallY = deltaY * 7.f / distance;

        overallX = overallX + (overallX * multiplier);
        overallY = overallY + (overallY * multiplier);

        SetLaserSpeedX(overallX);
        SetLaserSpeedY(overallY);
    }
}


void StarshipObject::ShootLaser(D2D1_POINT_2F p1, D2D1_POINT_2F p2, float thickness)
{
    gfx->DrawLine(p1.x, p1.y, p2.x, p2.y, 1.0f, 0.0f, 0.0f, thickness);
}


void StarshipObject::ResetLaser(void)
{
    laserX = GetCenterX();
    laserY = GetCenterY();
    laserSpeedX = 0.0f;
    laserSpeedY = 0.0f;
}



//---------------------------------
//=======================
// GETTERS
//=======================
//-------------------------------------------------
/**
* \brief Get the health
* \return float : health of the object.
*/
float StarshipObject::GetHealth(void)
{
    return health;
}

/**
* \brief Get the x-position of the laser
* \return float : laser x position.
*/
float StarshipObject::GetLaserX(void)
{
    return laserX;
}

/**
* \brief Get the y-position of the laser
* \return float : laser y position.
*/
float StarshipObject::GetLaserY(void)
{
    return laserY;
}

/**
* \brief Get the x speed of the laser
* \return float : laser x speed.
*/
float StarshipObject::GetLaserSpeedX(void)
{
    return laserSpeedX;
}

/**
* \brief Get the y speed of the laser
* \return float : laser y speed.
*/
float StarshipObject::GetLaserSpeedY(void)
{
    return laserSpeedY;
}

/**
* \brief Get the laser ammo that the starship has.
* \return int : The laser ammo.
*/
int StarshipObject::GetLaserAmmo(void)
{
    return laserAmmo;
}

/**
* \brief Gets a boolean of if the object is moving.
* \return bool : true if collision detected; false if no collision
*/
bool StarshipObject::IsMoving(void)
{
    return isMoving;
}

/**
* \brief Gets a boolean of if the object is dead with something.
* \return bool : true if dead; false if no dead
*/
bool StarshipObject::IsDead(void)
{
    return isDead;
}

/**
* \brief Gets a boolean of if the object is shooting.
* \return bool : true if is shooting detected; false if not shooting
*/
bool StarshipObject::IsLasering(void)
{
    return isFireLaser;
}


//---------------------------------
//=======================
// SETTERS
//=======================
/**
* \brief Sets the health of the object.
* \param h - float - The health
*/
void StarshipObject::SetHealth(float h)
{
    health = h;
}

/**
* \brief Sets the laser position (x-direction).
* \param x - float - The x position
*/
void StarshipObject::SetLaserX(float x)
{
    laserX = x;
}

/**
* \brief Sets the laser position (y-direction).
* \param y - float - The y position
*/
void StarshipObject::SetLaserY(float y)
{
    laserY = y;
}

/**
* \brief Sets the laser speed (x-direction).
* \param speedX - float - The x speed
*/
void StarshipObject::SetLaserSpeedX(float speedX)
{
    laserSpeedX = speedX;
}

/**
* \brief Sets the laser speed (y-direction).
* \param speedY - float - The y speed
*/
void StarshipObject::SetLaserSpeedY(float speedY)
{
    laserSpeedY = speedY;
}

/**
* \brief Set the laser ammo that the starship has.
* \param ammo - int - The ammo that starship will have
*/
void StarshipObject::SetLaserAmmo(int ammo)
{
    if (laserAmmo >= 0)
    {
        laserAmmo = ammo;
    }
}

/**
* \brief Sets if the object is moving.
* \param colliding - bool - A true/false value for moving
*/
void StarshipObject::SetIsMoving(bool moving)
{
    isMoving = moving;
}

/**
* \brief Sets if the object is dead.
* \param dead - bool - A true/false value for dead
*/
void StarshipObject::SetIsDead(bool dead)
{
    isDead = dead;
}

/**
* \brief Sets the object shooting state.
* \param shooting - bool - A true/false value for shooting
*/
void StarshipObject::SetIsLasering(bool shooting)
{
    isFireLaser = shooting;
}