/*
* PROJECT		: SETTrek
* FILE			: GameObject.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file implementation for the GameObject class.
*/
#include "GameObject.h"



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
GameObject::GameObject()
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;

	bitmap = NULL;
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
GameObject::~GameObject()
{
    if (bitmap)
    {
        bitmap->Release();
        bitmap = nullptr;
    }
}



//---------------------------------
//=======================
// COPY CONSTRUCTOR
//=======================
/**
* \brief Copy constructor for the object.
* \details Will copy the data member values for an object
*   to a new object.
* \param obj - const GameObject& - The object being copied
* \return None
*/
GameObject::GameObject(const GameObject& obj)
{
    if (this == &obj)
    {
    }
    else
    {
        this->renderArea = obj.renderArea;
        this->gfx = obj.gfx;
        this->bitmap = obj.bitmap;
        this->SetX1(obj.x1);
        this->SetX2(obj.x2);
        this->SetY1(obj.y1);
        this->SetY2(obj.y2);
    }
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
void GameObject::Init(LPCWSTR fileName)
{
	// Initialization of the asset - getting resources from file
	// The bitmap asset will be loaded to a temporary bitmap
	SpriteSheet sprite(fileName, gfx, &bitmap);
}


/**
* \brief Get the static reference to the Graphics.
* \param None
* \return Graphics* : The graphics.
*/
Graphics* GameObject::GetGfx(void)
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
void GameObject::Draw(float left, float top, float right, float bottom)
{
	// Refers to the location of where the bitmap
	// will be drawn, relative to the source (area) rectangle
	// The rectangle needs 4 points to be drawn!
	D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);
    
    gfx->GetDeviceContext()->DrawBitmap(
        bitmap,
        destRect,
        1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        renderArea);
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
void GameObject::Draw(float left, float top, float right, float bottom, float opacity)
{
    D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);

    gfx->GetDeviceContext()->DrawBitmap(
        bitmap,
        destRect,
        opacity,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        renderArea);
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
* \see void GameObject::Draw(float left, float top, float right, float bottom)
* \see void GameObject::Draw(float left, float top, float right, float bottom, float opacity)
* \return void
*/
void GameObject::Draw(float left, float top, float opacity)
{
    D2D1_RECT_F destRect = D2D1::RectF(left, top, bitmap->GetSize().width, bitmap->GetSize().height);

    gfx->GetDeviceContext()->DrawBitmap(
        bitmap,
        destRect,
        opacity,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        renderArea);
}


//---------------------------------
//=======================
// MUTATORS / SETTERS
//=======================
//-------------------------------------------------
// METHOD: GetBmp
/**
* \brief Get the bitmap of the game object.
* \param void
* \return ID2D1Bitmap* : The bitmap of this object.
*/
ID2D1Bitmap1* GameObject::GetBmp(void)
{
	return bitmap;
}

//-------------------------------------------------
// METHOD: GetBmpPixelSize
/**
* \brief Get the bitmap pixel size.
* \param void
* \return D2D1_SIZE_U : The pixel size of the bitmap.
*/
D2D1_SIZE_U GameObject::GetBmpPixelSize(void)
{
	return bitmap->GetPixelSize();
}

/**
* \brief Get the position center of the object..
* \return D2D1_POINT_2F : The center of the object.
*/
D2D1_POINT_2F GameObject::GetCenter(void) {
    float left = GetX1();
    float right = GetX2();
    float top = GetY1();
    float bottom = GetY2();

    return D2D1::Point2F((left + right) / 2, (top + bottom) / 2);
}

/**
* \brief Get position of the left-side of the object.
* \return float : The left-side of the object.
*/
float GameObject::GetX1(void) {
	return x1;
}

/**
* \brief Get position of the top-side of the object.
* \return float : The top-side of the object.
*/
float GameObject::GetY1(void) {
	return y1;
}

/**
* \brief Get position of the right-side of the object.
* \return float : The right-side of the object.
*/
float GameObject::GetX2(void) {
	return x2;
}

/**
* \brief Get position of the bottom-side of the object.
* \return float : The bottom-side of the object.
*/
float GameObject::GetY2(void) {
	return y2;
}



//---------------------------------
//=======================
// MUTATORS / SETTERS
//=======================
//-------------------------------------------------
// METHOD: SetBmp
/**
* \brief Set the bitmap of the game object.
* \details If there is an old bitmap resource, clean up the
*	bitmap resource. Then set the new bitmap resource.
* \param bmp - ID2D1Bitmap* - The new bitmap
* \return void
*/
void GameObject::SetBmp(ID2D1Bitmap1* bmp)
{
	if (bitmap)
	{
		bitmap->Release();
		bitmap = nullptr;
	}
	bitmap = bmp;
}

/**
* \brief Set position of the left-side of the object.
*/
void GameObject::SetX1(float x) {
	x1 = x;
}

/**
* \brief Set position of the top-side of the object.
*/
void GameObject::SetY1(float y) {
	y1 = y;
}

/**
* \brief Set position of the right-side of the object.
*/
void GameObject::SetX2(float x) {
	x2 = x;
}

/**
* \brief Set position of the bottom-side of the object.
*/
void GameObject::SetY2(float y) {
	y2 = y;
}