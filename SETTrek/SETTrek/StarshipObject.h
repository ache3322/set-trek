/*
* PROJECT		: SETTrek
* FILE			: StarshipObject.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class defintion for a StarshipObject.
*/
#pragma once
#include <Wincodec.h>
#include "Graphics.h"
#include "Object.h"
#include "GameObject.h"
#include "MoveableObject.h"




//===================
// CONSTANTS
//===================
#define kConstSpeed     2.0f
#define kDefaultHealth  10000.0f


/**
* \class MoveableObject
* \brief The MoveableObject encapsulates the attributes of a moving game object.
*/
class StarshipObject : public MoveableObject
{
private:

    float health;               //!< The health of the object
    float laserX;               //!< The position of the laser (x-direction)
    float laserY;               //!< The position of the laser (y-direction)
    float laserSpeedX;          //!< The laser speed in x-direction
    float laserSpeedY;          //!< The laser speed in y-direction

    bool isMoving;              //!< If the object is moving
    bool isDead;                //!< If the object is dead or not
    bool isFireLaser;            //!< If the object is shooting

public:

    //-Constructors
    StarshipObject();
    StarshipObject(float x, float y);
    StarshipObject(float xSpeed, float ySpeed, float baseSpeed);
    StarshipObject(float xSpeed, float ySpeed, float baseSpeed, float health);

    //-Destructor
    ~StarshipObject(void);

    //-Init Resources
    virtual void Init(LPCWSTR fileName);
    virtual Graphics* GetGfx(void);

    //-Draw Methods
    virtual void Draw(float left, float top, float right, float bottom);
    virtual void Draw(float left, float top, float right, float bottom, float opacity);
    virtual void Draw(float left, float top, float opacity = 1.0f);

    //-Methods
    void CalculateLaserSpeed(float deltaX, float deltaY, float multiplier = 0.0f);
    void ShootLaser(D2D1_POINT_2F p1, D2D1_POINT_2F p2, float thickness);
    void ResetLaser(void);

    //-Accessors
    float GetHealth(void);
    float GetLaserX(void);
    float GetLaserY(void);
    float GetLaserSpeedX(void);
    float GetLaserSpeedY(void);
    bool IsMoving(void);
    bool IsDead(void);
    bool IsLasering(void);

    //-Mutators
    void SetHealth(float h);
    void SetLaserX(float x);
    void SetLaserY(float y);
    void SetLaserSpeedX(float speedX);
    void SetLaserSpeedY(float speedY);
    void SetIsMoving(bool moving);
    void SetIsDead(bool dead);
    void SetIsLasering(bool shooting);
};