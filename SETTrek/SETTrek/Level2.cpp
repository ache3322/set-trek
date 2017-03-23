/*
* PROJECT		: SETTrek
* FILE			: Level2.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#include "Level2.h"


float enemyAngle = 0.0f;
float mouseXEnd = 0.0f;
float mouseYEnd = 0.0f;
bool isPlayerMoving = false;
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
    pEnemy = new MoveableObject(1.f, 1.f, gfx, screenSize);

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

	shipBaseEffect = EffectManager::CreateChroma(starShipBase->GetBmp(), 0.25f, 0);
	starShipBase->SetBmp(
		EffectManager::ConvertToBitmap(shipBaseEffect.Get(), starShipBase->GetBmpPixelSize())
	);

	shipDetailEffect = EffectManager::CreateChroma(starShipDetail->GetBmp(), 0.1f, 1);
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

    mouseXEnd = pPlayer->GetCenterX();
    mouseYEnd = pPlayer->GetCenterY();

    isPlayerMoving = false;

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
    pPlayer->CalculateAngle(deltaY, deltaX);

	//isPlayerMoving = true;
}


/**
* \brief Update the game and objects.
* \details Updates the game logic. The logic includes moving GameObjects
*	and any level decisions.
*/
void Level2::Update(void)
{
    float centerX = (pPlayer->GetX1() + pPlayer->GetX2()) / 2;
    float centerY = (pPlayer->GetY1() + pPlayer->GetY2()) / 2;

    if (isPlayerMoving)
    {
		float enemyDeltaX = pPlayer->GetCenterX() - pEnemy->GetCenterX();
		float enemyDeltaY = pPlayer->GetCenterY() - pEnemy->GetCenterY();
		pEnemy->CalculateSpeed(enemyDeltaX, enemyDeltaY);

		// Calc double the grid width - if enemy approaches within 2 grid spaces of player
		float doubleGridWidth = grid->GetWidth() * 2;
		float doubleGridHeight = grid->GetHeight() * 2;

		if ( (centerX + doubleGridWidth > pEnemy->GetCenterX() && centerX - doubleGridWidth < pEnemy->GetCenterX())
			&& (centerY + doubleGridHeight > pEnemy->GetCenterY() && centerY - doubleGridHeight < pEnemy->GetCenterY()) )
		{
			// Calculating 15% of the speed for X and Y
			pEnemy->CalculateSpeed(enemyDeltaX, enemyDeltaY, 0.15f);

			string output = "Enemy speed : " + to_string(pEnemy->GetSpeedX()) + " | " + to_string(pEnemy->GetSpeedY()) + "\n";
			OutputDebugStringA(output.c_str());
		}

        //===--------
        // Enemy Movement
        //
        if (centerX > pEnemy->GetCenterX() )
        {
            pEnemy->SetX1(pEnemy->GetX1() + pEnemy->GetSpeedX());
            pEnemy->SetX2(pEnemy->GetX2() + pEnemy->GetSpeedX());
        }
        if (centerX < pEnemy->GetCenterX() )
        {
            pEnemy->SetX1(pEnemy->GetX1() + pEnemy->GetSpeedX());
            pEnemy->SetX2(pEnemy->GetX2() + pEnemy->GetSpeedX());
        }
        if (centerY > pEnemy->GetCenterY() )
        {
            pEnemy->SetY1(pEnemy->GetY1() + pEnemy->GetSpeedY());
            pEnemy->SetY2(pEnemy->GetY2() + pEnemy->GetSpeedY());
        }
        if (centerY < pEnemy->GetCenterY() )
        {
            pEnemy->SetY1(pEnemy->GetY1() + pEnemy->GetSpeedY());
            pEnemy->SetY2(pEnemy->GetY2() + pEnemy->GetSpeedY());
        }

        if (pEnemy->GetX2() < 0)
        {
            vector<vector2> v2Grid = grid->GetGrid();
            pEnemy->SetX1(v2Grid[kCenterGrid].x);
            pEnemy->SetX2(v2Grid[kCenterGrid].x + grid->GetWidth());
        }
        enemyAngle = 180.f + (atan2f(enemyDeltaY, enemyDeltaX) * 180.f / PI);
    }
    //if (enemyAngle > 360.0f)
    //{
    //    enemyAngle = 0.0f;
    //}
    //
    //===--------

	//===--------
	// Player Ship Movement
	//
	if ( (mouseXEnd < centerX + kXThreshold) && (mouseXEnd > centerX - kXThreshold) 
        && (mouseYEnd < centerY + kYThreshold) && (mouseYEnd > centerY - kYThreshold) )
	{
		isPlayerMoving = false;
        pPlayer->SetSpeedX(0);
        pPlayer->SetSpeedY(0);
	}
    else
    {
        isPlayerMoving = true;
        pPlayer->SetX1(pPlayer->GetX1() + pPlayer->GetSpeedX());
        pPlayer->SetX2(pPlayer->GetX2() + pPlayer->GetSpeedX());
        pPlayer->SetY1(pPlayer->GetY1() + pPlayer->GetSpeedY());
        pPlayer->SetY2(pPlayer->GetY2() + pPlayer->GetSpeedY());
    }
	//
	//===--------


    //===--------
    // Starship Window Boundaries Check
    //
    if (pPlayer->GetX1() < 0)
    {
        pPlayer->SetX1(0);
        pPlayer->SetX2(0 + grid->GetWidth());
    }
    if (pPlayer->GetY1() < 0)
    {
        pPlayer->SetY1(grid->GetWindowHeight() - grid->GetHeight());
        pPlayer->SetY2(grid->GetWindowHeight());
    }

    // CHECK if right-side of Player leaves right screen
    if (pPlayer->GetX2() > grid->GetWindowWidth() - 5.0f)
    {
        pPlayer->SetX1(0);
        pPlayer->SetX2(0 + grid->GetWidth());
        // Generate another random set of coordinates for the planets
        grid->GenerateRandCoord();
        GenerateRandomPlanet();
    }
    if (pPlayer->GetY2() > grid->GetWindowHeight() - 5.0f)
    {
        pPlayer->SetY1(0);
        pPlayer->SetY2(grid->GetHeight());
        // Generate another random set of coordinates for the planets
        grid->GenerateRandCoord();
        GenerateRandomPlanet();
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

    //==----
	// 3. Draw the Starship
	vector<vector2> v2Grid = grid->GetGrid();

    float angle = pPlayer->GetAngle();
    D2D1_POINT_2F center = pPlayer->GetCenter();

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, center));

    pPlayer->Draw(pPlayer->GetX1(), pPlayer->GetY1(),
        pPlayer->GetX2(), pPlayer->GetY2());

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Identity());


    //==----
    // 4. Draw the Klingon Bird of Pray

    center = pEnemy->GetCenter();
    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(enemyAngle, center));

	pEnemy->Draw(pEnemy->GetX1(), pEnemy->GetY1(),
		pEnemy->GetX2(), pEnemy->GetY2());

    gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Identity());
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