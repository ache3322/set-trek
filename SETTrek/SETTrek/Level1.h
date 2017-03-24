/*
* PROJECT		: SETTrek
* FILE			: Level.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#pragma once
#include "Level.h"
#include "EffectManager.h"
#include "GameObject.h"
#include "Grid.h"
using namespace std;


//-CONSTANTS
#define kCenterGrid			49
#define kGridSquares		100



/**
* \class Level1
* \brief This is the first level.
* \details The level will contain all the associated logic and assets
*	associated for the initial level.
*/
class Level1 : public Level
{
private:

	D2D1_RECT_F screenSize;			//!< The size of the Game area (window)
	float windowWidth;				//!< The total width of the window (x-direction)
	float windowHeight;				//!< The total height of the window (y-direction)

	float gridWidth;				//!< The width of 1 grid space
	float gridHeight;				//!< The height of 1 grid space

	GameObject* pBackground;		//!< The background sprite
	GameObject* pStarShip;			//!< The starship sprite
	GameObject* pPlanet1;			//!< The first planet
	GameObject* pPlanet2;			//!< The second planet
	GameObject* pPlanet3;			//!< The third planet

	vector<GameObject *> chosenPlanets;			//!< Contains the planets (a random chance) that will be spawned

	vector<vector2> v2Grid;						//!< Contains the absolute position for the 10 by 10 grid. There are 100 squares in total
	vector<vector2> v2Rand;						//!< Contains the grid coordinates of where a random planet may spawn


public:

	void Load(D2D1_RECT_F size) override;		// For loading assets for the game level
	void Unload(void) override;					// For unloading assets from the game level
    void Process(int x, int y) override;
	void Update(void) override;					// For updating the game level
	void Render(void) override;					// For rendering the game level

	void GenerateGrid(void);
	void GenerateRandomCoord(void);
	void GenerateRandomPlanet(void);
};