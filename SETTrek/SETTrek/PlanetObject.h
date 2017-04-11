/*
* PROJECT		: SETTrek
* FILE			: PlanetObject.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class defintion for a PlanetObject.
*/
#pragma once
#include <random>
#include "GameObject.h"
using namespace std;



//===================
// CONSTANTS
//===================




//===================
// CLASS DEFINITION
//===================
/**
* \class PlanetObject
* \brief The PlanetObject encapsulates the attributes of a planet object.
*/
class PlanetObject : public GameObject
{
protected:

    int energyResource;             //!< The energy that the planet has
    int scienceResource;            //!< The science that the planet has

    bool isVisited;                 //!< Boolean of if the planet was visited by a ship
    bool isCurrent;                 //!< Boolean of if this is the current planet being visited

public:

    //-Constructors
    PlanetObject();
    PlanetObject(int energyResource, int scienceResource);

    //-Destructor
    ~PlanetObject(void);

    //-Init Resources
    virtual void Init(LPCWSTR fileName);
    virtual Graphics* GetGfx(void);

    //-Draw Methods
    virtual void Draw(float left, float top, float right, float bottom) override;
    virtual void Draw(float left, float top, float right, float bottom, float opacity) override;
    virtual void Draw(float left, float top, float opacity = 1.0f) override;

    //-Methods
    void GenerateRandomResources(void);

    //-Accessors
    int GetEnergyResource(void);
    int GetScienceResource(void);
    bool GetIsVisited(void);
    bool GetIsCurrent(void);

    //-Mutators
    void SetEnergyResource(int e);
    void SetScienceResource(int s);
    void SetIsVisited(bool visited);
    void SetIsCurrent(bool current);
};