/*
* PROJECT		: SETTrek
* FILE			: GameObject.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class defintion for a GameObject.
*/
#pragma once
#include <Wincodec.h>
#include "Graphics.h"
#include "SpriteSheet.h"



/**
* \class GameObject
* \brief The GameObject encapsulates the attributes of a game object.
* \details The class represents an object in a 2D space. It has a coordinate
*	system that allows for the object to be renderable and movable. As well,
*	a bitmap resource to hold the graphics.
*/
class GameObject
{
private:

	float x1;				//!< The starting x-position (left)
	float y1;				//!< The starting y-position (top)
	float x2;				//!< The ending x-position (right)
	float y2;				//!< The ending y-position (bottom)

	D2D1_RECT_F renderArea;	//!< The rectangle area/size of where the object will be drawn
	ID2D1Bitmap* bitmap;	//!< Holds the loaded Bitmap file
	Graphics* gfx;			//!< Reference to the Graphics object


public:

	//-Constructors
	GameObject(Graphics* graphics, D2D1_RECT_F area);

	//-Destructors
	~GameObject();

	void Init(LPCWSTR fileName);

	//-Draw Methods
	void Draw(float left, float top, float right, float bottom);

	//-Accessors
	float GetX1(void);
	float GetY1(void);
	float GetX2(void);
	float GetY2(void);

	//-Mutators
	void SetX1(float x);
	void SetY1(float y);
	void SetX2(float x);
	void SetY2(float y);
};