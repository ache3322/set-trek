/*
* PROJECT		: SETTrek
* FILE			: PlanetObject.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file implementation for the PlanetObject class.
*/
#include "PlanetObject.h"



//---------------------------------
//=======================
// CONSTRUCTORS
//=======================
/**
* \brief Constructor for the PlanetObject object.
* \details Set the values to a default value.
*/
PlanetObject::PlanetObject()
{
    energyResource = 300;
    scienceResource = 300;
    isVisited = false;
    isCurrent = false;
}


/**
* \brief Constructor for the PlanetObject object.
* \details Set the values to a default value.
* \param energyResource - int - How much energy the planet has
* \param scienceResource - int - How much science the planet has
*/
PlanetObject::PlanetObject(int energyResource, int scienceResource)
{
    this->energyResource = energyResource;
    this->scienceResource = scienceResource;
    isVisited = false;
    isCurrent = false;
}



//---------------------------------
//=======================
// DESTRUCTORS
//=======================
/**
* \brief Destroys the planet object.
*/
PlanetObject::~PlanetObject()
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
void PlanetObject::Init(LPCWSTR fileName)
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
Graphics* PlanetObject::GetGfx(void)
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
void PlanetObject::Draw(float left, float top, float right, float bottom)
{
    // Refers to the location of where the bitmap
    // will be drawn, relative to the source (area) rectangle
    // The rectangle needs 4 points to be drawn!
    D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);

    GameObject::Draw(left, top, right, bottom);
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
void PlanetObject::Draw(float left, float top, float right, float bottom, float opacity)
{
    D2D1_RECT_F destRect = D2D1::RectF(left, top, right, bottom);

    GameObject::Draw(GetX1(), GetY1(), GetX2(), GetY2(), opacity);
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
void PlanetObject::Draw(float left, float top, float opacity)
{
    D2D1_RECT_F destRect = D2D1::RectF(left, top, GameObject::GetBmp()->GetSize().width, GameObject::GetBmp()->GetSize().height);

    GameObject::Draw(GetX1(), GetY1(), GetX2(), GetY2(), opacity);
}



//---------------------------------
//=======================
// METHODS
//=======================
/**
* \brief Generates a random amount of resources for the planet
*/
void PlanetObject::GenerateRandomResources(void)
{
    const int kMaxEnergySize = 4;
    const int kMaxScienceSize = 2;

    // Randomly generate different amounts of resources based on an array index
    const int energyList[kMaxEnergySize] = { 200, 300, 400, 500};
    const int scienceList[kMaxScienceSize] = { 100, 200 };

    //uniform_int_distribution<int> distribution(100, 500);


    // Get random number between 0 to 4
     // Use this index to assign the energy resource
    energyResource = energyList[rand() % kMaxEnergySize];

    // Get random number between 0 to 4
    // Use this index to assign the energy resource
    scienceResource = scienceList[rand() % kMaxScienceSize];
}



//---------------------------------
//=======================
// GETTERS
//=======================
//-------------------------------------------------
/**
* \brief Get the energy of the planet.
* \return int : Energy that the planet has.
*/
int PlanetObject::GetEnergyResource(void) {
    return energyResource;
}

/**
* \brief Get the science of the planet.
* \return int : Science that the planet has.
*/
int PlanetObject::GetScienceResource(void) {
    return scienceResource;
}

/**
* \brief Get a boolean status of if this planet was visited.
* \return bool : true if visited; false if not
*/
bool PlanetObject::GetIsVisited(void) {
    return isVisited;
}

/**
* \brief Get a boolean status of if this is the current plane being visisted
* \return bool : true if current; false if not
*/
bool PlanetObject::GetIsCurrent(void) {
    return isCurrent;
}




//---------------------------------
//=======================
// SETTERS
//=======================
/**
* \brief Set the energy of the planet.
* \param e - int - How much energy
*/
void PlanetObject::SetEnergyResource(int e) {
    energyResource = e;
}

/**
* \brief Set the science of the planet.
* \param s - int - How much science
*/
void PlanetObject::SetScienceResource(int s) {
    scienceResource = s;
}

/**
* \brief Get a boolean status of if this planet was visited.
* \param visited - bool - If player visits the planet
*/
void PlanetObject::SetIsVisited(bool visited) {
    isVisited = visited;
}


/**
* \brief Set a boolean status of if this is the current plane being visisted
* \param current - bool - Status of if this is the current planet being visited
*/
void PlanetObject::SetIsCurrent(bool current) {
    isCurrent = current;
}