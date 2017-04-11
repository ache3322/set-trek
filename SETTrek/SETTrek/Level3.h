/*
* PROJECT		: SETTrek
* FILE			: Level3.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/03/08
* DESCRIPTION	: Level2 contains the game objects and scene for
*		where the StarShip (now the player ship) can move by mouse click.
*		As well, there is now a Klingon enemy ship that will chase after the
*		player.
*
*       Additional features in this level will focus on a combat system. This
*       combat system features starship lasers, missiles, explosions, etc.
*
*       As well, audio and sound will be implemented in this level.
*/
#pragma once
#include <string>
#include "Level.h"
#include "GameObject.h"
#include "PlanetObject.h"
#include "MoveableObject.h"
#include "StarshipObject.h"
using namespace std;




/**
* \class Level3
* \brief This is the third level.
* \details The level contains combat and sound.
*/
class Level3 : public Level
{
private:

    float windowWidth;				//!< The total width of the window (x-direction)
    float windowHeight;				//!< The total height of the window (y-direction)

    float mouseXEnd;                //!< The x-coordinate for the mouse click
    float mouseYEnd;                //!< The y-coordinate for the mouse click

    GameObject* pGUIMenu;           //!< Demonstration purposes - shows a UI of exploration
    GameObject* pBackground;		//!< The background sprite
    StarshipObject* pPlayer;		//!< The player starship - the U.S.S Conestoga
    StarshipObject* pEnemy;         //!< The enemy start ship - the Klingon Bird of Prey
    PlanetObject* pPlanet1;         //!< The first planet
    PlanetObject* pPlanet2;         //!< The second planet
    PlanetObject* pPlanet3;         //!< The thrid planet


    GameObject* pExplosion;         //!< The explosion bitmap
    GameObject* pShieldEffect;      //!< The sheidl effect

    vector<PlanetObject *> chosenPlanets;
    bool reGeneratePlanets;                      //!< A boolean flag to re-generate the planets again and again

public:

    void Load(void) override;		// For loading assets for the game level
    void Unload(void) override;					// For unloading assets from the game level
    void Update(void) override;					// For updating the game level
    void Render(void) override;					// For rendering the game level
    void Process(void) override;		// For processing input from the user and applying to game level

    void GenerateRandomPlanet(void);
    void RespawnShips(void);
    void GenerateNewScene(void);
    void RenderShipInfo(void);
    void RenderPlanetInfo(PlanetObject* planet);
};