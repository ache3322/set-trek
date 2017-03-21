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
GameObject::GameObject(Graphics* graphics, D2D1_RECT_F area)
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;

	bitmap = NULL;
	// Set reference to the Graphics object
	gfx = graphics;
	// Set the area to render the GameObject
	renderArea = area;
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
	if (bitmap) bitmap->Release();
}


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
ID2D1Bitmap* GameObject::GetBmp(void)
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

D2D1_POINT_2F GameObject::GetCenter(void) {
    float left = GetX1();
    float right = GetX2();
    float top = GetY1();
    float bottom = GetY2();

    return D2D1::Point2F((left + right) / 2, (top + bottom) / 2);
}

float GameObject::GetX1(void) {
	return x1;
}

float GameObject::GetY1(void) {
	return y1;
}

float GameObject::GetX2(void) {
	return x2;
}

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
void GameObject::SetBmp(ID2D1Bitmap* bmp)
{
	if (bitmap)
	{
		bitmap->Release();
		bitmap = nullptr;
	}
	bitmap = bmp;
}

void GameObject::SetX1(float x) {
	x1 = x;
}

void GameObject::SetY1(float y) {
	y1 = y;
}

void GameObject::SetX2(float x) {
	x2 = x;
}

void GameObject::SetY2(float y) {
	y2 = y;
}