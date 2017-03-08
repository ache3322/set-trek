/*
* PROJECT		: SETTrek
* FILE			: Level2.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#include "Level2.h"



/**
* \brief Loading all the game assets for this level.
* \details The method will load all the assets and setting
*	the values for this current level.
* \param size - D2D1_RECT_F - The dimensions of the window
* \return void
*/
void Level2::Load(D2D1_RECT_F size)
{
	// Ensure the random number generator is operation
	srand((unsigned int)time(NULL));

	screenSize = size;
	windowWidth = screenSize.right;
	windowHeight = screenSize.bottom;

	// Instantiate a Grid object
	grid = new Grid(windowWidth, windowHeight);

	// Loading the assets, resources, images, etc.
	pBackground = new GameObject(gfx, screenSize);
	pStarShip = new GameObject(gfx, screenSize);
	pPlanet1 = new GameObject(gfx, screenSize);
	pPlanet2 = new GameObject(gfx, screenSize);
	pPlanet3 = new GameObject(gfx, screenSize);
	unique_ptr<GameObject> starShipBase(new GameObject(gfx, screenSize));
	unique_ptr<GameObject> starShipDetail(new GameObject(gfx, screenSize));

	pBackground->Init(L".\\assets\\SectorBackground.bmp");
	pStarShip->Init(L".\\assets\\ShipBase.bmp");
	pPlanet1->Init(L".\\assets\\Planet1.bmp");
	pPlanet2->Init(L".\\assets\\Planet2.bmp");
	pPlanet3->Init(L".\\assets\\Planet3.bmp");
	starShipBase->Init(L".\\assets\\ShipBase.bmp");
	starShipDetail->Init(L".\\assets\\ShipDetail.bmp");

	//---------------------
	// Applying EffectManager effects

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

	// DEBUG/TEST
	pPlayer = new MoveableObject(5.0, 0, gfx, screenSize);
	pPlayer->Init(L".\\assets\\ShipBase.bmp");
	pPlayer->SetBmp(EffectManager::ConvertToBitmap(compositeKey.Get(), pStarShip->GetBmpPixelSize()));
	// DEBUG/TEST

	//--------------------

	// Generate the grid positions/coordinates AND
	// Generate the initial random coordinates and planets
	grid->ConstructGrid();
	grid->GenerateRandCoord();
	GenerateRandomPlanet();
}


/**
* \brief Unloading any resources or assets from the level.
* \param void
* \return void
*/
void Level2::Unload(void)
{
	// Clean up any resources
	chosenPlanets.clear();
	if (grid) delete grid;
	if (pBackground) delete pBackground;
	if (pStarShip) delete pStarShip;
	if (pPlanet1) delete pPlanet1;
	if (pPlanet2) delete pPlanet2;
	if (pPlanet3) delete pPlanet3;

	if (pPlayer) delete pPlayer;
}


/**
* \brief Update the game and objects.
* \details Updates the game logic. The logic includes moving GameObjects
*	and any level decisions.
*/
void Level2::Update(void)
{
	// The start ship moves grid to grid
	pStarShip->SetX1(pStarShip->GetX1() + grid->GetWidth());

	// The Starship reached the end of "sector space" (edge of screen)
	if (pStarShip->GetX1() > windowWidth)
	{
		// Reset the ship's position to the beginning
		pStarShip->SetX1(0);
	}

	pPlayer->SetX1(pPlayer->GetX1() + pPlayer->GetSpeedX());
	if (pPlayer->GetX1() > grid->GetWindowWidth())
	{
		pPlayer->SetX1(0);


		// Generate another random set of coordinates for the planets
		grid->GenerateRandCoord();
		GenerateRandomPlanet();
	}
}


/**
* \brief Render the game objects to the screen.
* \details For this particular level, the game objects
*	are drawn to the screen.
*/
void Level2::Render(void)
{
	float gridWidth = grid->GetWidth();
	float gridHeight = grid->GetHeight();

	//1. Draw the Background before other objects
	pBackground->Draw(0, 0, windowWidth, windowHeight);

	// 2. Draw the random-chanced Planets
	vector<vector2> v2Rand = grid->GetRandCoord();
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
	vector<vector2> v2Grid = grid->GetGrid();
	pStarShip->Draw(pStarShip->GetX1(), v2Grid[kCenterGrid].y,
		pStarShip->GetX1() + gridWidth, v2Grid[kCenterGrid].y + gridHeight);

	//------------------------------
	// DEBUG: SHOWING GRID POINTS
	for (int i = 0; i < v2Grid.size(); ++i)
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

	pPlayer->Draw(pPlayer->GetX1(), v2Grid[kCenterGrid].y,
		pPlayer->GetX1() + gridWidth, v2Grid[kCenterGrid].y + gridHeight);
}

/**
* \brief Generate the random planet to spawn on to the chosen grids.
* \param void
* \return void
*/
void Level2::GenerateRandomPlanet(void)
{
	int randomChance = 0;

	chosenPlanets.clear();

	// For each chosen grid coordinate - we choose
	// what planets to spawn at that coordinate. It
	// could be Earth, Mars, or Jupiter
	for (int i = 0; i < grid->GetRandCoordSize(); ++i)
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