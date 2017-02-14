/*
* PROJECT		: SETTrek
* FILE			: Level.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#include "Level1.h"



/**
* \brief
* \details
* \param
* \return
*/
void Level1::Load(void)
{
	// Ensure the random number generator is operation
	srand((unsigned int)time(NULL));

	// TEMP
	windowWidth = 1008.0f; // Original: 1024
	windowHeight = 729.0f; // Original: 768

	gridWidth = windowWidth / kNumberOfGrid;
	gridHeight = windowHeight / kNumberOfGrid;

	shipX = 0.0f;

	// Loading the assets, resources, images, etc.
	pBackground = new SpriteSheet(L".\\assets\\SectorBackground.bmp", gfx);
	pStarShip = new SpriteSheet(L".\\assets\\ShipBase.bmp", gfx);
	pPlanet1 = new SpriteSheet(L".\\assets\\Planet1.bmp", gfx);
	pPlanet2 = new SpriteSheet(L".\\assets\\Planet2.bmp", gfx);
	pPlanet3 = new SpriteSheet(L".\\assets\\Planet3.bmp", gfx);
	numberOfGeneratedPlanets = 0;


	// Generate the grid positions/coordinates
	GenerateGrid();
	GenerateRandomGrid();
	GenerateRandomPlanet();
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::Unload(void)
{
	// Clean up any resources
	if (pBackground) delete pBackground;
	if (pStarShip) delete pStarShip;
	if (pPlanet1) delete pPlanet1;
	if (pPlanet2) delete pPlanet2;
	if (pPlanet3) delete pPlanet3;
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::Update(void)
{
	shipX = shipX + gridWidth;

	// The ship has left the screen
	if (shipX > windowWidth)
	{
		// Reset the ship's position to the beginning
		shipX = 0;

		// Generate another random set of coordinates for the planets
		chosenGrid.clear();
		GenerateRandomGrid();
		chosenPlanets.clear();
		GenerateRandomPlanet();
	}
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::Render(void)
{
	pBackground->Draw(0, 0, windowWidth, windowHeight);
	pStarShip->Draw(shipX, spaceGrid[kMiddleGrid - 1].first, gridWidth + shipX, spaceGrid[kMiddleGrid - 1].first + gridHeight);


	for (int i = 0; i < chosenGrid.size(); ++i)
	{
		chosenPlanets[i]->Draw(
			chosenGrid[i].first,
			chosenGrid[i].second,
			chosenGrid[i].first + gridWidth,
			chosenGrid[i].second + gridHeight
		);
	}

	//for (int i = 0; i < spaceGrid.size(); ++i)
	//{
	//	pStarShip->Draw(
	//		spaceGrid[i].first,
	//		spaceGrid[i].second,
	//		spaceGrid[i].first + gridWidth,
	//		spaceGrid[i].second + gridHeight
	//		);
	//}
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::GenerateGrid(void)
{
	int row = 0;		// X-axis
	int col = 0;		// Y-axis

	for (col = 0; col < kNumberOfGrid; ++col)
	{
		for (int row = 0; row < kNumberOfGrid; ++row)
		{
			// <x, y>
			pair<float, float> coord;
			coord.first = row * gridWidth;
			coord.second = col * gridHeight;

			spaceGrid.push_back(coord);
		}
	}
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::GenerateRandomGrid(void)
{
	bool isSpawn = false;
	int chance = 0;
	
	// For each spaceGrid position, calculate the chance
	// for a planet to spawn. There is a 1 in 20 (5%) chance
	// that a planet will spawn...
	for (int i = 0; i < spaceGrid.size(); ++i)
	{
		isSpawn = (rand() % 100) < 5;

		if (isSpawn)
		{
			// These are the chose grid positions where
			// a planet is going to be drawn at
			pair<float, float> coord;
			coord.first = spaceGrid[i].first;
			coord.second = spaceGrid[i].second;
			chosenGrid.push_back(coord);

			++numberOfGeneratedPlanets;
			isSpawn = false;
		}
	}
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::GenerateRandomPlanet(void)
{
	int chosenPlanet = 0;

	// For each chosen grid coordinate - we choose
	// what planets to spawn at that coordinate. It
	// could be Earth, Mars, or Jupiter
	for (size_t i = 0; i < chosenGrid.size(); ++i)
	{
		chosenPlanet = rand() % 3;
		if (chosenPlanet == 0)
		{
			chosenPlanets.push_back(pPlanet1);
		}
		else if (chosenPlanet == 1)
		{
			chosenPlanets.push_back(pPlanet2);
		}
		else if (chosenPlanet == 2)
		{
			chosenPlanets.push_back(pPlanet3);
		}
	}
}