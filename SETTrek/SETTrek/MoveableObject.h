/*
* PROJECT		: SETTrek
* FILE			: MoveableObject.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: 
*/
#pragma once
#include <Wincodec.h>
#include "Graphics.h"
#include "GameObject.h"


//===================
// CONSTANTS
//===================
#define kConstSpeed     2.0f


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

public:

	//-Constructors
	MoveableObject(Graphics* graphics, D2D1_RECT_F area);
	MoveableObject(float x, float y, Graphics* graphics, D2D1_RECT_F area);

	//-Destructor
	~MoveableObject(void);

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

	//-Mutators
	void SetSpeedX(float x);
	void SetSpeedY(float y);
    void SetBaseSpeed(float s);
    void SetAngle(float a);
};