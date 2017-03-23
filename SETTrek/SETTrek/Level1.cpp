/*
* PROJECT		: SETTrek
* FILE			: Level.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#include "Level1.h"



/**
* \brief Loading all the game assets for this level.
* \details The method will load all the assets and setting
*	the values for this current level.
* \param size - D2D1_RECT_F - The dimensions of the window
* \return void
*/
void Level1::Load(D2D1_RECT_F size)
{
	// Ensure the random number generator is operation
	srand((unsigned int)time(NULL));

	screenSize = size;
	windowWidth = screenSize.right;
	windowHeight = screenSize.bottom;

	gridWidth = windowWidth / kNumberOfGrid;
	gridHeight = windowHeight / kNumberOfGrid;

	// Loading the assets, resources, images, etc.
	pBackground = new GameObject();
	pStarShip = new GameObject();
	pPlanet1 = new GameObject();
	pPlanet2 = new GameObject();
	pPlanet3 = new GameObject();
	unique_ptr<GameObject> starShipBase(new GameObject());
	unique_ptr<GameObject> starShipDetail(new GameObject());

	pBackground->Init(L".\\assets\\SectorBackground.bmp");
	pStarShip->Init(L".\\assets\\ShipBase.bmp");
	pPlanet1->Init(L".\\assets\\Planet1.bmp");
	pPlanet2->Init(L".\\assets\\Planet2.bmp");
	pPlanet3->Init(L".\\assets\\Planet3.bmp");
	starShipBase->Init(L".\\assets\\ShipBase.bmp");
	starShipDetail->Init(L".\\assets\\ShipDetail.bmp");

	//---------------------
	// EffectManager stuff

	ComPtr<ID2D1Effect> chromaKey;
	// Do the Chroma Effect on each resource!
	chromaKey = EffectManager::CreateChroma(pPlanet1->GetBmp());
	pPlanet1->SetBmp(
		EffectManager::ConvertToBitmap(chromaKey.Get(), pPlanet1->GetBmpPixelSize())
	);
	chromaKey.Get()->Release();

	chromaKey = EffectManager::CreateChroma(pPlanet2->GetBmp());
	pPlanet2->SetBmp(
		EffectManager::ConvertToBitmap(chromaKey.Get(), pPlanet2->GetBmpPixelSize())
	);
	chromaKey.Get()->Release();

	chromaKey = EffectManager::CreateChroma(pPlanet3->GetBmp());
	pPlanet3->SetBmp(
		EffectManager::ConvertToBitmap(chromaKey.Get(), pPlanet3->GetBmpPixelSize())
	);

	//---------------------
	ComPtr<ID2D1Effect> shipBaseEffect;
	ComPtr<ID2D1Effect> shipDetailEffect;

	shipBaseEffect = EffectManager::CreateChroma(starShipBase->GetBmp());
	starShipBase->SetBmp(
		EffectManager::ConvertToBitmap(shipBaseEffect.Get(), starShipBase->GetBmpPixelSize())
	);

	shipDetailEffect = EffectManager::CreateChroma(starShipDetail->GetBmp());
	starShipDetail->SetBmp(
		EffectManager::ConvertToBitmap(shipDetailEffect.Get(), starShipDetail->GetBmpPixelSize())
	);

	//---------------------

	// Do the composite on the ship
	ComPtr<ID2D1Effect> compositeKey;
	compositeKey = EffectManager::CreateComposite(starShipBase->GetBmp(), starShipDetail->GetBmp());
	pStarShip->SetBmp(EffectManager::ConvertToBitmap(compositeKey.Get(), pStarShip->GetBmpPixelSize()));
	//--------------------

	// Generate the grid positions/coordinates
	GenerateGrid();
	// Generate the initial random coordinates and planets
	GenerateRandomCoord();
	GenerateRandomPlanet();
}


/**
* \brief Unloading any resources or assets from the level.
* \param void
* \return void
*/
void Level1::Unload(void)
{
	// Clean up any resources
	chosenPlanets.clear();
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
		GenerateRandomCoord();
		GenerateRandomPlanet();
	}
}


/**
* \brief Render the game objects to the screen.
* \details For this particular level, the game objects
*	are drawn to the screen.
*/
void Level1::Render(void)
{
	//1. Draw the Background before other objects
	pBackground->Draw(0, 0, windowWidth, windowHeight);

	// 2. Draw the random-chanced Planets
	for (int i = 0; i < v2Rand.size(); ++i)
	{
		chosenPlanets[i]->Draw(
			v2Rand[i].x,
			v2Rand[i].y,
			v2Rand[i].x + gridWidth,
			v2Rand[i].y + gridHeight
		);
	}

	// 3. Draw the Starship
	pStarShip->Draw(pStarShip->GetX1(), v2Grid[kCenterGrid].y,
		pStarShip->GetX1() + gridWidth, v2Grid[kCenterGrid].y + gridHeight);


	// DEBUG: SHOWING GRID POINTS
	for (int i = 0; i < kGridSquares; ++i)
	{
		gfx->DrawCircle(
			v2Grid[i].x,
			v2Grid[i].y,
			8.0,
			255.0,
			255.0,
			255.0
		);
	}
}


/**
* \brief Generating the grid for this level. 
* \details The grid is a 10 by 10 grid. In total there are
*	100 grids in the area. The absolute position is calculated
*	from each grid-point.
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
			// The col is along the X-axis
			// The row is along the Y-axis
			vector2 vCoord = { col*  gridWidth, row * gridHeight };
			v2Grid.push_back(vCoord);
		}
	}
}


/**
* \brief Generate a random grid coordinate for spawning the planet.
* \details The random grid generation chooses a grid point from
*	the already generated points. For each grid point, a 5% chance
*	that a planet may be spawned happens.
*/
void Level1::GenerateRandomCoord(void)
{
	bool doSpawn = false;

	v2Rand.clear();
	
	// For each grid position, calculate the chance
	// for a planet to spawn. There is a 1 in 20 (5%) chance
	// that a planet will spawn...
	for (int i = 0; i < v2Grid.size(); ++i)
	{
		doSpawn = (rand() % 100) < 5;

		if (doSpawn)
		{
			// These are the chosen grid positions 
			// where a planet is going to be drawn at
			vector2 vCoord = { v2Grid[i].x, v2Grid[i].y };
			v2Rand.push_back(vCoord);

			doSpawn = false;
		}
	}
}


/**
* \brief Generate the random planet to spawn on to the chosen grids.
* \param void
* \return void
*/
void Level1::GenerateRandomPlanet(void)
{
	int randomChance = 0;

	chosenPlanets.clear();

	// For each chosen grid coordinate - we choose
	// what planets to spawn at that coordinate. It
	// could be Earth, Mars, or Jupiter
	for (int i = 0; i < v2Rand.size(); ++i)
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