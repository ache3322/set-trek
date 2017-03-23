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
#include "Object.h"
#include "SpriteSheet.h"



/**
* \class GameObject
* \brief The GameObject encapsulates the attributes of a game object.
* \details The class represents an object in a 2D space. It has a coordinate
*	system that allows for the object to be renderable and movable. As well,
*	a bitmap resource to hold the graphics.
*/
class GameObject : public Object
{
private:

	float x1;				//!< The starting x-position (left)
	float y1;				//!< The starting y-position (top)
	float x2;				//!< The ending x-position (right)
	float y2;				//!< The ending y-position (bottom)

    ID2D1Bitmap1* bitmap;   //!< Holds the loaded Bitmap file

public:

	//-Constructors
	GameObject();

	//-Destructors
	~GameObject();

    //-Copy Constructors
    GameObject(const GameObject& obj);

    //-Init Resources
	virtual void Init(LPCWSTR fileName);
    virtual Graphics* GetGfx(void);

	//-Draw Methods
	void Draw(float left, float top, float right, float bottom);

	//-Accessors
	ID2D1Bitmap1* GetBmp(void);
	D2D1_SIZE_U GetBmpPixelSize(void);
    D2D1_POINT_2F GetCenter(void);
	virtual float GetX1(void);
    virtual float GetY1(void);
    virtual float GetX2(void);
    virtual float GetY2(void);

	//-Mutators
	void SetBmp(ID2D1Bitmap1* bmp);
	virtual void SetX1(float x);
	virtual void SetY1(float y);
	virtual void SetX2(float x);
	virtual void SetY2(float y);
};