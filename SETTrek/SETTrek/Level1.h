/*
* PROJECT		: SETTrek
* FILE			: Level.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#pragma once
#include "Level.h"
#include <time.h>
#include <vector>
using namespace std;


//-CONSTANTS
#define kNumberOfGrid		10
#define kMiddleGrid			4



/**
* \class Level1
* \brief This is the first level.
* \details The level will contain all the associated logic and assets
*	associated for the initial level.
*/
class Level1 : public Level
{
private:

	RECT screenSize;				//!< The size of the Window (the game area)
	SpriteSheet* pBackground;		//!< The background sprite for the game
	SpriteSheet* pStarShip;			//!< The starship
	SpriteSheet* pPlanet1;			//!< The first planet
	SpriteSheet* pPlanet2;			//!< The second planet
	SpriteSheet* pPlanet3;			//!< The third planet

	float shipX;					//!< For moving the ship across the screen

	float windowWidth;				//!< The total width of the window (x-direction)
	float windowHeight;				//!< The total height of the window (y-direction)

	float gridWidth;				//!< The width of 1 grid space
	float gridHeight;				//!< The height of 1 grid space


	int numberOfGeneratedPlanets;

	vector<pair<float, float>> spaceGrid;		//!< Contains the absolute position for the 10 by 10 grid
	vector<pair<float, float>> chosenGrid;		//!< Contains the grid coordinates of where a random planet may spawn
	vector<SpriteSheet *> chosenPlanets;			//!< Contains the planets (a random chance) that will be spawned

public:

	void Load(void) override;		// For loading assets for the game level
	void Unload(void) override;		// For unloading assets from the game level
	void Update(void) override;		// For updating the game level
	void Render(void) override;		// For rendering the game level

	void GenerateGrid(void);
	void GenerateRandomGrid(void);
	void GenerateRandomPlanet(void);
};