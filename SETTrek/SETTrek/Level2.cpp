/*
* PROJECT		: SETTrek
* FILE			: Level2.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#include "Level2.h"


float angle = 0.0f;
float mouseXEnd = 0.0f;
float mouseYEnd = 0.0f;

bool isPlayerMoving = false;

float overallX = 0.0f;
float overallY = 0.0f;
float distance = 0.0f;
D2D1::Matrix3x2F trans;


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
	pPlanet1 = new GameObject(gfx, screenSize);
	pPlanet2 = new GameObject(gfx, screenSize);
	pPlanet3 = new GameObject(gfx, screenSize);
	unique_ptr<GameObject> starShipBase(new GameObject(gfx, screenSize));
	unique_ptr<GameObject> starShipDetail(new GameObject(gfx, screenSize));
    pEnemy = new MoveableObject(1.0f, 1.0f, gfx, screenSize);

	pBackground->Init(L".\\assets\\SectorBackground.bmp");
	pPlanet1->Init(L".\\assets\\Planet1.bmp");
	pPlanet2->Init(L".\\assets\\Planet2.bmp");
	pPlanet3->Init(L".\\assets\\Planet3.bmp");
	starShipBase->Init(L".\\assets\\ShipBase.bmp");
	starShipDetail->Init(L".\\assets\\ShipDetail.bmp");
    pEnemy->Init(L".\\assets\\EnemyShip.bmp");


	//---------------------
	// Applying EffectManager effects

	ComPtr<ID2D1Effect> chromaKey;
	// Do the Chroma Effect on each resource!
	chromaKey = EffectManager::CreateChroma(pPlanet1->GetBmp());
	pPlanet1->SetBmp(
		EffectManager::ConvertToBitmap(chromaKey.Get(), pPlanet1->GetBmpPixelSize())
	);

	chromaKey = EffectManager::CreateChroma(pPlanet2->GetBmp());
	pPlanet2->SetBmp(
		EffectManager::ConvertToBitmap(chromaKey.Get(), pPlanet2->GetBmpPixelSize())
	);

	chromaKey = EffectManager::CreateChroma(pPlanet3->GetBmp());
	pPlanet3->SetBmp(
		EffectManager::ConvertToBitmap(chromaKey.Get(), pPlanet3->GetBmpPixelSize())
	);
    
    // Loading the effect for the enemy ship
    chromaKey = EffectManager::CreateChroma(pEnemy->GetBmp(), 0.0f, 0.0f, 1.0f, 0.15f);
    pEnemy->SetBmp(
        EffectManager::ConvertToBitmap(chromaKey.Get(), pEnemy->GetBmpPixelSize())
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

	// DEBUG/TEST
	pPlayer = new MoveableObject(0, 0, gfx, screenSize);
	pPlayer->Init(L".\\assets\\ShipBase.bmp");
	pPlayer->SetBmp(EffectManager::ConvertToBitmap(compositeKey.Get(), pPlayer->GetBmpPixelSize()));
	// DEBUG/TEST

	//--------------------

	// Generate the grid positions/coordinates AND
	// Generate the initial random coordinates and planets
	grid->ConstructGrid();
	grid->GenerateRandCoord();
	GenerateRandomPlanet();


    //--------------------
    //-- Set the initial position of the StarShip
    vector<vector2> v2Grid = grid->GetGrid();
    pPlayer->SetX1(0);
    pPlayer->SetX2(grid->GetWidth());
    pPlayer->SetY1(v2Grid[kCenterGrid].y);
    pPlayer->SetY2(v2Grid[kCenterGrid].y + grid->GetHeight());

    mouseXEnd = pPlayer->GetX1();
    mouseYEnd = pPlayer->GetY1();

	//--------------------
	//-- Set the initial position of the Enemy Ship
	pEnemy->SetX1(v2Grid[kCenterGrid].x);
	pEnemy->SetX2(v2Grid[kCenterGrid].x + grid->GetWidth());
	pEnemy->SetY1(v2Grid[kCenterGrid].y);
	pEnemy->SetY2(v2Grid[kCenterGrid].y + grid->GetHeight());
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
	if (pPlanet1) delete pPlanet1;
	if (pPlanet2) delete pPlanet2;
	if (pPlanet3) delete pPlanet3;

	if (pPlayer) delete pPlayer;
    if (pEnemy) delete pEnemy;
}


/**
* \brief Process the player's input.
* \details The input can be as simple as a mouse click event.
* \param x - int - The mouse X position
* \param y - int - The mouse Y position
*/
void Level2::Process(int x, int y)
{
    // Get the current mouse click position
    mouseXEnd = (float)x;
    mouseYEnd = (float)y;

    float centerX = (pPlayer->GetX1() + pPlayer->GetX2()) / 2;
    float centerY = (pPlayer->GetY1() + pPlayer->GetY2()) / 2;

    float deltaX = mouseXEnd - centerX;
    float deltaY = mouseYEnd - centerY;
    pPlayer->CalculateSpeed(deltaX, deltaY);

    // Calculate the angle
    angle = atan2f(deltaY, deltaX) * 180.f / PI;

	isPlayerMoving = true;
}


/**
* \brief Update the game and objects.
* \details Updates the game logic. The logic includes moving GameObjects
*	and any level decisions.
*/
void Level2::Update(void)
{
    // The start ship moves grid to grid
    //pStarShip->SetX1(pStarShip->GetX1() + grid->GetWidth());

	if (pPlayer->GetX1() > grid->GetWindowWidth())
	{
		pPlayer->SetX1(0);

		// Generate another random set of coordinates for the planets
		grid->GenerateRandCoord();
		GenerateRandomPlanet();
	}

	float centerX = (pPlayer->GetX1() + pPlayer->GetX2()) / 2;
	float centerY = (pPlayer->GetY1() + pPlayer->GetY2()) / 2;

	if (isPlayerMoving)
	{
		if (centerX > pEnemy->GetCenterX() + kXThreshold)
		{
			pEnemy->SetX1(pEnemy->GetX1() + pEnemy->GetSpeedX());
			pEnemy->SetX2(pEnemy->GetX2() + pEnemy->GetSpeedX());
		}
		if (centerX < pEnemy->GetCenterX() - kXThreshold)
		{
			pEnemy->SetX1(pEnemy->GetX1() - pEnemy->GetSpeedX());
			pEnemy->SetX2(pEnemy->GetX2() - pEnemy->GetSpeedX());
		}
		if (centerY > pEnemy->GetCenterY() + kYThreshold)
		{
			pEnemy->SetY1(pEnemy->GetY1() + pEnemy->GetSpeedY());
			pEnemy->SetY2(pEnemy->GetY2() + pEnemy->GetSpeedY());
		}
		if (centerY < pEnemy->GetCenterY() - kYThreshold)
		{
			pEnemy->SetY1(pEnemy->GetY1() - pEnemy->GetSpeedY());
			pEnemy->SetY2(pEnemy->GetY2() - pEnemy->GetSpeedY());
		}
	}

	if (pEnemy->GetX2() < 0)
	{
		vector<vector2> v2Grid = grid->GetGrid();
		pEnemy->SetX1(v2Grid[kCenterGrid].x);
		pEnemy->SetX2(v2Grid[kCenterGrid].x + grid->GetWidth());
	}

	//===--------
	// Player Ship Movement
	//
    // Moving the StarShip X-Axis logic
    if (mouseXEnd > centerX + kXThreshold)
    {
        // Moving to the RIGHT
        pPlayer->SetX1(pPlayer->GetX1() + pPlayer->GetSpeedX());
        pPlayer->SetX2(pPlayer->GetX2() + pPlayer->GetSpeedX());
    }
    if (mouseXEnd < centerX - kXThreshold)
    {
        // Moving to the LEFT
        pPlayer->SetX1(pPlayer->GetX1() + pPlayer->GetSpeedX());
        pPlayer->SetX2(pPlayer->GetX2() + pPlayer->GetSpeedX());
    }
    // Moving the StarShip Y-Axis logic
    if (mouseYEnd > centerY + kYThreshold)
    {
        // Moving DOWN
        pPlayer->SetY1(pPlayer->GetY1() + pPlayer->GetSpeedY());
        pPlayer->SetY2(pPlayer->GetY2() + pPlayer->GetSpeedY());
    }
    if (mouseYEnd < centerY - kYThreshold)
    {
        // Moving UP
        pPlayer->SetY1(pPlayer->GetY1() + pPlayer->GetSpeedY());
        pPlayer->SetY2(pPlayer->GetY2() + pPlayer->GetSpeedY());
    }

	if ( (mouseXEnd < centerX + kXThreshold) && (mouseXEnd > centerX - kXThreshold) )
	{
		isPlayerMoving = false;
	}

    trans = D2D1::Matrix3x2F::Translation(0, 0);
	//
	//===--------


    //===--------
    // Prevent Starship from going off the left-side of screen
    //
    if (pPlayer->GetX1() < 0)
    {
        pPlayer->SetX1(0);
        pPlayer->SetX2(0 + grid->GetWidth());
    }
    if (pPlayer->GetY1() < 0)
    {
        pPlayer->SetY1(0);
        pPlayer->SetY2(grid->GetHeight());
    }
    //
    //===--------
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

    D2D1_POINT_2F center = pPlayer->GetCenter();
    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, center) * trans);

	pPlayer->Draw(pPlayer->GetX1(), pPlayer->GetY1(),
		pPlayer->GetX2(), pPlayer->GetY2());

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Identity());


    //==----
    // 4. Draw the Klingon Bird of Pray
	pEnemy->Draw(pEnemy->GetX1(), pEnemy->GetY1(),
		pEnemy->GetX2(), pEnemy->GetY2());
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