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


/**
* \class MoveableObject
* \brief The MoveableObject encapsulates the attributes of a moving game object.
*/
class MoveableObject : public GameObject
{
private:

	float speedX;				//!< The moving speed - in x-direction
	float speedY;				//!< The moving speed - in y-direction

public:

	//-Constructors
	MoveableObject(Graphics* graphics, D2D1_RECT_F area);
	MoveableObject(float x, float y, Graphics* graphics, D2D1_RECT_F area);

	//-Destructor
	~MoveableObject(void);

	//-Accessors
	float GetSpeedX(void) const;
	float GetSpeedY(void) const;

	//-Mutators
	void SetSpeedX(float x);
	void SetSpeedY(float y);
};