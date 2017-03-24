/*
* PROJECT		: SETTrek
* FILE			: MoveableObject.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class defintion for a MoveableObject.
*/
#pragma once
#include <Wincodec.h>
#include "Graphics.h"
#include "Object.h"
#include "GameObject.h"


//===================
// CONSTANTS
//===================
#define kConstSpeed     2.0f
#define kDefaultHealth  10000.0f


/**
* \class MoveableObject
* \brief The MoveableObject encapsulates the attributes of a moving game object.
*/
class MoveableObject : public GameObject
{
private:

	float speedX;				//!< The moving speed - in x-direction
	float speedY;				//!< The moving speed - in y-direction
    float baseSpeed;            //!< The base speed of the object
    float angle;                //!< The angle of the moveableobject

    float health;               //!< The health of the object

    bool isColliding;           //!< Collision detected

public:

	//-Constructors
	MoveableObject();
	MoveableObject(float x, float y);
    MoveableObject(float xSpeed, float ySpeed, float baseSpeed);

	//-Destructor
	~MoveableObject(void);

    //-Init Resources
    virtual void Init(LPCWSTR fileName);
    virtual Graphics* GetGfx(void);

    //-Methods
    void CalculateSpeed(float deltaX, float deltaY);
	void CalculateSpeed(float deltaX, float deltaY, float multiplier);
    void CalculateAngle(float opposite, float ajacent);

	//-Accessors
	float GetSpeedX(void) const;
	float GetSpeedY(void) const;
    float GetBaseSpeed(void);
	float GetCenterX(void);
	float GetCenterY(void);
    float GetAngle(void);
    float GetHealth(void);
    bool IsColliding(void);

	//-Mutators
	void SetSpeedX(float x);
	void SetSpeedY(float y);
    void SetBaseSpeed(float s);
    void SetAngle(float a);
    void SetHealth(float h);
    void SetIsColliding(bool colliding);
};