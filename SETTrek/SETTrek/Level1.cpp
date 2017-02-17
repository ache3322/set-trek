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
void Level1::Load(D2D1_RECT_F size)
{
	// Ensure the random number generator is operation
	srand((unsigned int)time(NULL));

	screenSize = size;
	windowWidth = screenSize.right;		// Original: 1024
	windowHeight = screenSize.bottom;	// Original: 768, 729, 772

	gridWidth = windowWidth / kNumberOfGrid;
	gridHeight = windowHeight / kNumberOfGrid;

	// Loading the assets, resources, images, etc.
	pBackground = new GameObject(gfx, screenSize);
	pStarShip = new GameObject(gfx, screenSize);
	pPlanet1 = new GameObject(gfx, screenSize);
	pPlanet2 = new GameObject(gfx, screenSize);
	pPlanet3 = new GameObject(gfx, screenSize);
	GameObject* starShipBase = new GameObject(gfx, screenSize);
	GameObject* starShipDetail = new GameObject(gfx, screenSize);

	pBackground->Init(L".\\assets\\SectorBackground.bmp");
	pStarShip->Init(L".\\assets\\ShipBase.bmp");
	pPlanet1->Init(L".\\assets\\Planet1.bmp");
	pPlanet2->Init(L".\\assets\\Planet2.bmp");
	pPlanet3->Init(L".\\assets\\Planet3.bmp");
	starShipBase->Init(L".\\assets\\ShipBase.bmp");
	starShipDetail->Init(L".\\assets\\ShipDetail.bmp");

	//---------------------

	ComPtr<ID2D1Effect> chromaKey;
	// Do the Chroma Effect on each resource!
	chromaKey = EffectManager::CreateChroma(gfx, pPlanet1->GetBitmap());
	pPlanet1->SetBitmap(
		EffectManager::ConvertToBitmap(gfx, chromaKey.Get(), pPlanet1->GetBitmapPixelSize())
	);

	chromaKey = EffectManager::CreateChroma(gfx, pPlanet2->GetBitmap());
	pPlanet2->SetBitmap(
		EffectManager::ConvertToBitmap(gfx, chromaKey.Get(), pPlanet2->GetBitmapPixelSize())
	);

	chromaKey = EffectManager::CreateChroma(gfx, pPlanet3->GetBitmap());
	pPlanet3->SetBitmap(
		EffectManager::ConvertToBitmap(gfx, chromaKey.Get(), pPlanet3->GetBitmapPixelSize())
	);

	chromaKey = EffectManager::CreateChroma(gfx, starShipBase->GetBitmap());
	starShipBase->SetBitmap(
		EffectManager::ConvertToBitmap(gfx, chromaKey.Get(), starShipBase->GetBitmapPixelSize())
	);

	chromaKey = EffectManager::CreateChroma(gfx, starShipDetail->GetBitmap());
	starShipDetail->SetBitmap(
		EffectManager::ConvertToBitmap(gfx, chromaKey.Get(), starShipDetail->GetBitmapPixelSize())
	);

	//---------------------

	// Do the composite on the ship
	ComPtr<ID2D1Effect> compositeKey;
	compositeKey = EffectManager::CreateComposite(gfx, starShipBase->GetBitmap(), starShipDetail->GetBitmap());
	pStarShip->SetBitmap(EffectManager::ConvertToBitmap(gfx, compositeKey.Get(), pStarShip->GetBitmapPixelSize()));

	delete starShipBase;
	delete starShipDetail;
	//--------------------

	// Generate the grid positions/coordinates
	GenerateGrid();
	// Generate the initial random coordinates and planets
	GenerateRandomCoord();
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
* \brief Update the game and objects.
* \details Updates the game logic. The logic includes moving GameObjects
*	and any level decisions.
*/
void Level1::Update(void)
{
	// The start ship moves grid to grid
	pStarShip->SetX1(pStarShip->GetX1() + gridWidth);

	// The Starship reached the end of "sector space" (edge of screen)
	if (pStarShip->GetX1() > windowWidth)
	{
		// Reset the ship's position to the beginning
		pStarShip->SetX1(0);

		// Generate another random set of coordinates for the planets
		randCoord.clear();
		GenerateRandomCoord();
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
	//1. Draw the Background before other objects
	pBackground->Draw(0, 0, windowWidth, windowHeight);

	// 3. Draw the random-chanced Planets
	for (int i = 0; i < randCoord.size(); ++i)
	{
		chosenPlanets[i]->Draw(
			randCoord[i].first,
			randCoord[i].second,
			randCoord[i].first + gridWidth,
			randCoord[i].second + gridHeight
		);
	}

	// 2. Draw the Starship
	pStarShip->Draw(pStarShip->GetX1(), grid[kCenterGrid].second,
		pStarShip->GetX1() + gridWidth, grid[kCenterGrid].second + gridHeight);
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::GenerateGrid(void)
{
	int row = 0;
	int col = 0;

	for (row = 0; row < kNumberOfGrid; ++row)
	{
		for (col = 0; col < kNumberOfGrid; ++col)
		{
			// The pair takes in pair coordinates: (x, y), (col, row)
			pair<float, float> coordinate;

			// The col is along the X-axis
			coordinate.first = col * gridWidth;
			// The row is along the Y-axis
			coordinate.second = row * gridHeight;
			grid.push_back(coordinate);
		}
	}
}


/**
* \brief
* \details
* \param
* \return
*/
void Level1::GenerateRandomCoord(void)
{
	bool doSpawn = false;
	
	// For each grid position, calculate the chance
	// for a planet to spawn. There is a 1 in 20 (5%) chance
	// that a planet will spawn...
	for (int i = 0; i < grid.size(); ++i)
	{
		doSpawn = (rand() % 100) < 5;

		if (doSpawn)
		{
			// These are the chose grid positions where
			// a planet is going to be drawn at
			pair<float, float> coord;
			coord.first = grid[i].first;
			coord.second = grid[i].second;
			randCoord.push_back(coord);

			doSpawn = false;
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
	int randomChance = 0;

	// For each chosen grid coordinate - we choose
	// what planets to spawn at that coordinate. It
	// could be Earth, Mars, or Jupiter
	for (size_t i = 0; i < randCoord.size(); ++i)
	{
		randomChance = rand() % 3;
		if (randomChance == 0) {
			chosenPlanets.push_back(pPlanet1);
		}
		else if (randomChance == 1) {
			chosenPlanets.push_back(pPlanet2);
		}
		else if (randomChance == 2) {
			chosenPlanets.push_back(pPlanet3);
		}
	}
}