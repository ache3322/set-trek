/*
* PROJECT		: SETTrek
* FILE			: Level2.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/03/08
* DESCRIPTION	: Level2 contains the game objects and scene for
*		where the StarShip (now the player ship) can move by mouse click.
*		As well, there is now a Klingon enemy ship that will chase after the
*		player.
*/
#pragma once
#include <vector>
#include <memory>
#include "Level.h"
#include "EffectManager.h"
#include "GameObject.h"
#include "MoveableObject.h"
#include "Grid.h"
using namespace std;



/**
* \class Level1
* \brief This is the first level.
* \details The level will contain all the associated logic and assets
*	associated for the initial level.
*/
class Level2 : public Level
{
private:

	D2D1_RECT_F screenSize;			//!< The size of the Game area (window)
	float windowWidth;				//!< The total width of the window (x-direction)
	float windowHeight;				//!< The total height of the window (y-direction)

	GameObject* pBackground;		//!< The background sprite
	MoveableObject* pPlayer;		//!< The player starship - the U.S.S Conestoga
	GameObject* pStarShip;			//!< The starship sprite
	GameObject* pPlanet1;			//!< The first planet
	GameObject* pPlanet2;			//!< The second planet
	GameObject* pPlanet3;			//!< The third planet

	Grid* grid;
	vector<GameObject *> chosenPlanets;			//!< Contains the planets (a random chance) that will be spawned

public:

	void Load(D2D1_RECT_F size) override;		// For loading assets for the game level
	void Unload(void) override;					// For unloading assets from the game level
	void Update(void) override;					// For updating the game level
	void Render(void) override;					// For rendering the game level

	void GenerateRandomPlanet(void);
};