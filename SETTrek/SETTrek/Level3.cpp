/*
* PROJECT		: SETTrek
* FILE			: Level3.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	: The CPP implementation for the Level3 class.
* CREDIT        : Explosion assets from https://gameartpartners.com/game-art-fx/
*/
#include "Level3.h"



/**
* \brief Loading all the game assets for this level.
* \details The method will load all the assets and setting
*	the values for this current level.
* \return void
*/
void Level3::Load()
{
    // Ensure the random number generator is operation
    srand((unsigned int)time(NULL));

    // Get the window width and height
    windowWidth = screenSize.right;
    windowHeight = screenSize.bottom;

    // Loading the assets, resources, images, etc.
    pBackground = new GameObject();
    pPlanet1 = new PlanetObject();
    pPlanet2 = new PlanetObject();
    pPlanet3 = new PlanetObject();
    unique_ptr<GameObject> starShipBase(new GameObject());
    unique_ptr<GameObject> starShipDetail(new GameObject());
    pEnemy = new StarshipObject(0.0f, 0.0f, 3.5f, 5000.0f);

    pBackground->Init(L".\\assets\\SectorBackground.bmp");
    pPlanet1->Init(L".\\assets\\Planet1.bmp");
    pPlanet2->Init(L".\\assets\\Planet2.bmp");
    pPlanet3->Init(L".\\assets\\Planet3.bmp");
    starShipBase->Init(L".\\assets\\ShipBase.bmp");
    starShipDetail->Init(L".\\assets\\ShipDetail.bmp");
    pEnemy->Init(L".\\assets\\EnemyShip.bmp");

    //---------------------
    // Loading Exploration GUI (WIP)
    pGUIMenu = new GameObject();
    pGUIMenu->Init(L".\\assets\\planet_scan.bmp");

    // Loading the explosion effect
    pExplosion = new GameObject();
    pExplosion->Init(L".\\assets\\Explosion.bmp");

    // Loading the shield effect
    pShieldEffect = new GameObject();
    pShieldEffect->Init(L".\\assets\\energy_shield.bmp");

    //
    //---------------------


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

    // Chroma key on the explosion
    chromaKey = EffectManager::CreateChroma(pExplosion->GetBmp(), 0.8f);
    pExplosion->SetBmp(
        EffectManager::ConvertToBitmap(chromaKey.Get(), pExplosion->GetBmpPixelSize())
    );

    // Remove background using chroma
    chromaKey = EffectManager::CreateChroma(pShieldEffect->GetBmp(), 0.5f);
    pShieldEffect->SetBmp(
        EffectManager::ConvertToBitmap(chromaKey.Get(), pShieldEffect->GetBmpPixelSize())
    );

    //---------------------
    //
    ComPtr<ID2D1Effect> shipBaseEffect;
    ComPtr<ID2D1Effect> shipDetailEffect;

    shipBaseEffect = EffectManager::CreateChroma(starShipBase->GetBmp(), 0.55f, 0);
    starShipBase->SetBmp(
        EffectManager::ConvertToBitmap(shipBaseEffect.Get(), starShipBase->GetBmpPixelSize())
    );

    shipDetailEffect = EffectManager::CreateChroma(starShipDetail->GetBmp(), 0.4f, 0);
    starShipDetail->SetBmp(
        EffectManager::ConvertToBitmap(shipDetailEffect.Get(), starShipDetail->GetBmpPixelSize())
    );
    //
    //---------------------

    // Do the composite on the ship
    ComPtr<ID2D1Effect> compositeKey;
    compositeKey = EffectManager::CreateComposite(starShipBase->GetBmp(), starShipDetail->GetBmp());

    // DEBUG/TEST
    pPlayer = new StarshipObject(0, 0, 5.0f);
    pPlayer->Init(L".\\assets\\ShipBase.bmp");
    pPlayer->SetBmp(EffectManager::ConvertToBitmap(compositeKey.Get(), pPlayer->GetBmpPixelSize()));
    // DEBUG/TEST


    //--------------------

    // Generate the grid positions/coordinates AND
    // Generate the initial random coordinates and planets
    Level::grid->ConstructGrid();
    Level::grid->GenerateRandCoord();
    GenerateRandomPlanet();
    reGeneratePlanets = false;


    //--------------------
    //-- Set the initial position of the StarShip
    vector<vector2> v2Grid = Level::grid->GetGrid();
    pPlayer->SetX1(0);
    pPlayer->SetX2(grid->GetWidth());
    pPlayer->SetY1(v2Grid[kPlayerSpawn].y);
    pPlayer->SetY2(v2Grid[kPlayerSpawn].y + grid->GetHeight());

    // Set the mouse position at the center of the player
    mouseXEnd = pPlayer->GetCenterX();
    mouseYEnd = pPlayer->GetCenterY();
    Input::I_leftMouseX = mouseXEnd;
    Input::I_leftMouseY = mouseYEnd;

    //--------------------
    //-- Set the initial position of the Enemy Ship
    pEnemy->SetX1(v2Grid[kEnemySpawn].x);
    pEnemy->SetX2(v2Grid[kEnemySpawn].x + grid->GetWidth());
    pEnemy->SetY1(v2Grid[kEnemySpawn].y);
    pEnemy->SetY2(v2Grid[kEnemySpawn].y + grid->GetHeight());
}


/**
* \brief Unloading any resources or assets from the level.
* \param void
* \return void
*/
void Level3::Unload(void)
{
    // Clean up any resources
    if (Level::grid) delete Level::grid;
    if (pBackground) delete pBackground;
    if (pPlanet1) delete pPlanet1;
    if (pPlanet2) delete pPlanet2;
    if (pPlanet3) delete pPlanet3;

    if (pPlayer) delete pPlayer;
    if (pEnemy) delete pEnemy;

    if (pExplosion) delete pExplosion;
    if (pShieldEffect) delete pShieldEffect;
}


/**
* \brief Process the player's input.
* \details The input can be as simple as a mouse click event.
*/
void Level3::Process(void)
{
    // Did the player "right click"?
    if (Input::isRightClick)
    {
        // Does the player have enough ammo?
        if (pPlayer->GetLaserAmmo() >= 100)
        {
            // If so, then we set the mode to laser mode!
            pPlayer->SetIsLasering(true);
            // Decrease the ammo count
            pPlayer->SetLaserAmmo(pPlayer->GetLaserAmmo() - 100);

            float centerX = (pPlayer->GetX1() + pPlayer->GetX2()) / 2;
            float centerY = (pPlayer->GetY1() + pPlayer->GetY2()) / 2;

            float deltaX = Input::I_rightMouseX - centerX;
            float deltaY = Input::I_rightMouseY - centerY;

            pPlayer->CalculateLaserSpeed(deltaX, deltaY, 1.5f);

            // Get the "end" point of the x and y so that the laser
            // will appear to move from the center of the player ship
            // to where the right-mouse click is
            pPlayer->SetLaserX(centerX);
            pPlayer->SetLaserY(centerY);

        }
        Input::isRightClick = false;
    }

    // Otherwise, the player is "moving"
    if (Input::isLeftClick)
    {
        // Get the current mouse click position
        mouseXEnd = (float)Input::I_leftMouseX;
        mouseYEnd = (float)Input::I_leftMouseY;

        float centerX = (pPlayer->GetX1() + pPlayer->GetX2()) / 2;
        float centerY = (pPlayer->GetY1() + pPlayer->GetY2()) / 2;

        float deltaX = mouseXEnd - centerX;
        float deltaY = mouseYEnd - centerY;


        // Calculate the expected speed
        pPlayer->CalculateSpeed(deltaX, deltaY);

        // Calculate the angle
        pPlayer->CalculateAngle(deltaY, deltaX);
        
        Input::isLeftClick = false;
    }


    if (Level::mode == explorationMode)
    {
        for(PlanetObject* p : chosenPlanets)
        {
            if (p->GetIsCurrent())
            {
                switch (Input::I_keyValue)
                {
                case KEY_1:
                    if (p->GetEnergyResource() > 0)
                    {
                        pPlayer->SetHealth(pPlayer->GetHealth() + p->GetEnergyResource());
                        p->SetEnergyResource(0);
                    }
                    break;

                case KEY_2:
                    if (p->GetScienceResource() > 0)
                    {
                        pPlayer->SetLaserAmmo(pPlayer->GetLaserAmmo() + p->GetScienceResource());
                        p->SetScienceResource(0);
                    }
                    break;

                case KEY_3:
                    Input::I_keyValue = 0x00;
                    p->SetIsCurrent(false);
                    Level::mode = spaceMode;
                    break;
                }
            }
        }

        Input::isKeyDown = false;
    }
}


/**
* \brief Update the game and objects.
* \details Updates the game logic. The logic includes moving GameObjects
*	and any level decisions.
*/
void Level3::Update(void)
{
    if (Level::mode == explorationMode)
    {
        return;
    }

    float centerX = pPlayer->GetCenterX();
    float centerY = pPlayer->GetCenterY();
    float enemyCenterX = pEnemy->GetCenterX();
    float enemyCenterY = pEnemy->GetCenterY();


    //===--------
    // Enemy Collision Detection
    //
    float enemyBoundaryX = grid->GetWidth() * 1.0f;
    float enemyBoundaryY = grid->GetHeight() * 1.0f;
    if ((enemyCenterX - enemyBoundaryX < pPlayer->GetCenterX()) && (pPlayer->GetCenterX() < enemyCenterX + enemyBoundaryX)
        && (enemyCenterY - enemyBoundaryY < pPlayer->GetCenterY()) && (pPlayer->GetCenterY() < enemyCenterY + enemyBoundaryY))
    {
        if (!pEnemy->IsDead())
        {
            // Player is taking DAMAGE!
            pPlayer->SetHealth(pPlayer->GetHealth() - 100);
        }
    }
    else
    {
    }
    //
    //===--------

    //===--------
    // Planet Collision Detection
    //
    // NOTE: Collision Detection should happen before moving the Player
    for (int i = 0; i < grid->GetRandCoordSize(); ++i)
    {
        D2D1_POINT_2F planetCenter = chosenPlanets[i]->GetCenter();
        float planetCenterX = planetCenter.x;
        float planetCenterY = planetCenter.y;
        float halfGridWidth = (grid->GetWidth() * 0.5f);
        float halfGridHeight = (grid->GetHeight() * 0.5f);

        // Iterate through each Planet coordinates to determine
        // if the Player has collided with a certain point...
        if ((pPlayer->GetCenterX() < planetCenterX + halfGridWidth && pPlayer->GetCenterX() > planetCenterX - halfGridWidth)
            && (pPlayer->GetCenterY() < planetCenterY + halfGridHeight && pPlayer->GetCenterY() > planetCenterY - halfGridHeight))
        {
            // Only goto exploration mode if and only if
            // they have not visited the planet
            if (chosenPlanets[i]->GetIsVisited() == false)
            {
                pPlayer->SetIsColliding(true);
                chosenPlanets[i]->SetIsVisited(true);
                chosenPlanets[i]->SetIsCurrent(true);

                // Change the mode type to exploration mode
                Level::mode = explorationMode;
            }
            break;
        }
        else
        {
            pPlayer->SetIsColliding(false);
            //chosenPlanets[i]->SetIsVisited(false);
        }
    }
    //
    //===--------

    //===--------
    // Laser Collision Detection
    //
    if (pPlayer->IsLasering())
    {
        if ((enemyCenterX - (enemyBoundaryX * 0.5f) < pPlayer->GetLaserX()) && (pPlayer->GetLaserX() < enemyCenterX + (enemyBoundaryX * 0.5f))
            && (enemyCenterY - (enemyBoundaryY * 0.5f) < pPlayer->GetLaserY()) && (pPlayer->GetLaserY() < enemyCenterY + (enemyBoundaryY * 0.5f)))
        {
            // Enemy is taking damage!!!
            pEnemy->SetHealth(pEnemy->GetHealth() - 1000);
        }
    }
    //
    //===--------


    //===--------
    // Enemy Movement
    //
    if (pPlayer->IsMoving() && !pEnemy->IsDead())
    {
        // Calc double the grid width - if enemy approaches within 2 grid spaces of player
        float doubleGridWidth = grid->GetWidth() * 2;
        float doubleGridHeight = grid->GetHeight() * 2;

        float enemyDeltaX = pPlayer->GetCenterX() - pEnemy->GetCenterX();
        float enemyDeltaY = pPlayer->GetCenterY() - pEnemy->GetCenterY();

        pEnemy->CalculateSpeed(enemyDeltaX, enemyDeltaY);

        // Check the if Klingon ship is within 2 grid spaces of the Player ship...
        // if the Klingon is in 2 grid spaces, then the speed is increased by 10%
        if ((centerX + doubleGridWidth > pEnemy->GetCenterX() && centerX - doubleGridWidth < pEnemy->GetCenterX())
            && (centerY + doubleGridHeight > pEnemy->GetCenterY() && centerY - doubleGridHeight < pEnemy->GetCenterY()))
        {
            // Calculating 15% of the speed for X and Y
            pEnemy->CalculateSpeed(enemyDeltaX, enemyDeltaY, 0.15f);
        }

        //===--------
        // Enemy Movement
        //
        if ((centerX < pEnemy->GetCenterX() && centerX > pEnemy->GetCenterX())
            && (centerY > pEnemy->GetCenterY() && centerY < pEnemy->GetCenterY()))
        {
            // Do nothing if Klingon ship reaches the Player ship
        }
        else
        {
            pEnemy->SetX1(pEnemy->GetX1() + pEnemy->GetSpeedX());
            pEnemy->SetX2(pEnemy->GetX2() + pEnemy->GetSpeedX());
            pEnemy->SetY1(pEnemy->GetY1() + pEnemy->GetSpeedY());
            pEnemy->SetY2(pEnemy->GetY2() + pEnemy->GetSpeedY());
        }

        if (pEnemy->GetX2() < 0)
        {
            vector<vector2> v2Grid = grid->GetGrid();
            pEnemy->SetX1(v2Grid[kCenterGrid].x);
            pEnemy->SetX2(v2Grid[kCenterGrid].x + grid->GetWidth());
        }

        float enemyAngle = 180.f + (atan2f(enemyDeltaY, enemyDeltaX) * 180.f / PI);
        pEnemy->SetAngle(enemyAngle);
        //
        //===--------
    }
    //
    //===--------


    //===--------
    // Player Ship Movement
    //
    if ((mouseXEnd < centerX + 3.0f) && (mouseXEnd > centerX - 3.0f)
        && (mouseYEnd < centerY + 3.0f) && (mouseYEnd > centerY - 3.0f))
    {
        pPlayer->SetIsMoving(false);
        pPlayer->SetSpeedX(0);
        pPlayer->SetSpeedY(0);
    }
    else
    {
        pPlayer->SetIsMoving(true);
        pPlayer->SetX1(pPlayer->GetX1() + pPlayer->GetSpeedX());
        pPlayer->SetX2(pPlayer->GetX2() + pPlayer->GetSpeedX());
        pPlayer->SetY1(pPlayer->GetY1() + pPlayer->GetSpeedY());
        pPlayer->SetY2(pPlayer->GetY2() + pPlayer->GetSpeedY());
    }
    //
    //===--------

    //===--------
    // Laser Movement
    //
    float laserX = pPlayer->GetLaserX();
    float laserY = pPlayer->GetLaserY();

    if ( (Input::I_rightMouseX < laserX + 10.0f) && (Input::I_rightMouseX > laserX - 10.0f)
        && (Input::I_rightMouseY < laserY + 10.0f) && (Input::I_rightMouseY > laserY - 10.0f) )
    {
        pPlayer->SetIsLasering(false);
        pPlayer->SetLaserSpeedX(0);
        pPlayer->SetLaserSpeedY(0);
    }

    pPlayer->SetLaserX(pPlayer->GetLaserX() + pPlayer->GetLaserSpeedX());
    pPlayer->SetLaserY(pPlayer->GetLaserY() + pPlayer->GetLaserSpeedY());
    //
    //===--------


    //===--------
    // Starship Window Boundaries Check
    //
    // BUG: If the Player ship is close to the window borders it must
    //  appear at the opposite-side of the screen. However, since the game loop
    //  is iterated very fast - the Player ship will 'bounce' back and forth. To
    //  compensate for this - a padding is used to spawn the ship beyond the boundaries.
    //
    // CHECK the right-side of the screen
    if (pPlayer->GetX2() > grid->GetWindowWidth())
    {
        // The player appears on the left-side
        pPlayer->SetX1(0);
        pPlayer->SetX2(0 + grid->GetWidth());
        GenerateNewScene();
    }
    // CHECK the top-side of the screen
    if (pPlayer->GetY1() < 0.0f)
    {
        // The player appears on the bottom-side
        pPlayer->SetY1(grid->GetWindowHeight() - grid->GetHeight() - kWindowPadding);
        pPlayer->SetY2(grid->GetWindowHeight() - kWindowPadding);
        GenerateNewScene();
    }
    // CHECK the bottom-side of the screen
    else if (pPlayer->GetY2() > grid->GetWindowHeight())
    {
        // The player appears on the top-side
        pPlayer->SetY1(0 + kWindowPadding);
        pPlayer->SetY2(grid->GetHeight() + kWindowPadding);
        GenerateNewScene();
    }
    //
    //===--------

    //===--------
    // Process Player Health
    //
    if (pPlayer->GetHealth() < 0.0f)
    {
        // Restart the level
        RespawnShips();
    }

    if (pEnemy->GetHealth() < 0.0f)
    {
        // Set the Enemy status to "Dead"
        pEnemy->SetIsDead(true);
    }
    //
    //===--------
}


/**
* \brief Render the game objects to the screen.
* \details For this particular level, the game objects
*	are drawn to the screen.
*/
void Level3::Render(void)
{
    if (Level::mode == explorationMode)
    {
        //1. Draw the Background before other objects
        pGUIMenu->Draw(0, 0, windowWidth, windowHeight);

        for (int i = 0; i < grid->GetRandCoordSize(); ++i)
        {
            if (chosenPlanets[i]->GetIsVisited() && chosenPlanets[i]->GetIsCurrent())
            {
                RenderPlanetInfo(chosenPlanets[i]);
            }
        }

        return;
    }


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
    // Draw the Player's laser
    //
    if (pPlayer->IsLasering())
    {
        D2D1_POINT_2F point1;
        point1.x = pPlayer->GetCenterX();
        point1.y = pPlayer->GetCenterY();
        pPlayer->ShootLaser(point1, D2D1::Point2F(pPlayer->GetLaserX(), pPlayer->GetLaserY()), 5.0f);
    }

    //==----
    // 3. Draw the Starship
    //
    vector<vector2> v2Grid = grid->GetGrid();

    pPlayer->Draw(pPlayer->GetX1(), pPlayer->GetY1(),
        pPlayer->GetX2(), pPlayer->GetY2());
    
    // Player ship EXPLODED!!!
    if (pPlayer->GetHealth() < 450.0f)
    {
        pExplosion->Draw(pPlayer->GetX1() - 15, pPlayer->GetY1() - 15,
            pPlayer->GetX2() + 15, pPlayer->GetY2() + 15);
    }
    // Player has SHIELD EFFECT
    else if (pPlayer->GetHealth() > 5000.0f)
    {
        pShieldEffect->Draw(pPlayer->GetX1() - 20, pPlayer->GetY1() - 20,
            pPlayer->GetX2() + 20, pPlayer->GetY2() + 20, 0.2f);
    }


    //==----
    // 4. Draw the Klingon Bird of Pray
    //
    if (!pEnemy->IsDead())
    {
        pEnemy->Draw(pEnemy->GetX1(), pEnemy->GetY1(),
            pEnemy->GetX2(), pEnemy->GetY2());
    }
    if (pEnemy->IsDead())
    {
        pExplosion->Draw(pEnemy->GetX1() - 15, pEnemy->GetY1() - 15,
            pEnemy->GetX2() + 15, pEnemy->GetY2() + 15);
    }

    // Render the text and any other information
    RenderShipInfo();
}

/**
* \brief Generate the random planet to spawn on to the chosen grids.
* \param void
* \return void
*/
void Level3::GenerateRandomPlanet(void)
{
    int randomChance = 0;
    PlanetObject* tmpPlanet = nullptr;

    chosenPlanets.clear();

    // For each chosen grid coordinate - we choose
    // what planets to spawn at that coordinate. It
    // could be Earth, Mars, or Jupiter
    for (int i = 0; i < grid->GetRandCoordSize(); ++i)
    {
        float left = grid->GetRandCoord()[i].x;
        float right = grid->GetRandCoord()[i].x + grid->GetWidth();
        float top = grid->GetRandCoord()[i].y;
        float bottom = grid->GetRandCoord()[i].y + grid->GetHeight();

        randomChance = rand() % 3;
        if (randomChance == 0) {
            tmpPlanet = new PlanetObject();
            tmpPlanet->SetBmp(pPlanet1->GetBmp());
            tmpPlanet->GenerateRandomResources();
            chosenPlanets.push_back(tmpPlanet);
        }
        else if (randomChance == 1) {
            tmpPlanet = new PlanetObject();
            tmpPlanet->SetBmp(pPlanet2->GetBmp());
            tmpPlanet->GenerateRandomResources();
            chosenPlanets.push_back(tmpPlanet);
        }
        else if (randomChance == 2) {
            tmpPlanet = new PlanetObject();
            tmpPlanet->SetBmp(pPlanet3->GetBmp());
            tmpPlanet->GenerateRandomResources();
            chosenPlanets.push_back(tmpPlanet);
        }

        // Set the coordinates for the planet
        chosenPlanets[i]->SetX1(left);
        chosenPlanets[i]->SetX2(right);
        chosenPlanets[i]->SetY1(top);
        chosenPlanets[i]->SetY2(bottom);
    }
}


/*
* \brief Respawns the ships in the starting positions
* \param None
* \return None
*/
void Level3::RespawnShips(void)
{
    // Respawning the player
    vector<vector2> v2Grid = grid->GetGrid();
    pPlayer->SetX1(0);
    pPlayer->SetX2(grid->GetWidth());
    pPlayer->SetY1(v2Grid[kPlayerSpawn].y);
    pPlayer->SetY2(v2Grid[kPlayerSpawn].y + grid->GetHeight());
    // Reset the health and the angle of the ship
    pPlayer->SetHealth(kDefaultHealth);
    pPlayer->SetAngle(0.0f);
    // Stopo the player from moving
    pPlayer->ResetSpeed();
    // Reset the laser position
    pPlayer->ResetLaser();
    // Replenish the ammo
    pPlayer->SetLaserAmmo(kDefaultAmmoLimit);

    mouseXEnd = pPlayer->GetCenterX();
    mouseYEnd = pPlayer->GetCenterY();

    pPlayer->SetIsMoving(false);
    pPlayer->SetIsDead(false);
    pPlayer->SetIsLasering(false);

    // Respawn the Klingon ship
    pEnemy->SetX1(v2Grid[kEnemySpawn].x);
    pEnemy->SetX2(v2Grid[kEnemySpawn].x + grid->GetWidth());
    pEnemy->SetY1(v2Grid[kEnemySpawn].y);
    pEnemy->SetY2(v2Grid[kEnemySpawn].y + grid->GetHeight());
    pEnemy->SetAngle(0.0f);
    pEnemy->SetHealth(5000.0f);
    pEnemy->SetIsDead(false);

    // Load a new scene
    grid->GenerateRandCoord();
    GenerateRandomPlanet();

    Sleep(750);
}


/*
* \brief Generates a new scene
* \param None
* \return None
*/
void Level3::GenerateNewScene(void)
{
    // Keep track of the mouse position
    mouseXEnd = pPlayer->GetCenterX();
    mouseYEnd = pPlayer->GetCenterY();

    // Load a new scene
    grid->GenerateRandCoord();
    GenerateRandomPlanet();

    if (pEnemy->IsDead())
    {
        // Respawning the enemy ship
        vector<vector2> v2Grid = grid->GetGrid();
        pEnemy->SetX1(v2Grid[kMiddleGrid].x);
        pEnemy->SetX2(v2Grid[kMiddleGrid].x + grid->GetWidth());
        pEnemy->SetY1(v2Grid[kMiddleGrid].y);
        pEnemy->SetY2(v2Grid[kMiddleGrid].y + grid->GetHeight());
        pEnemy->SetAngle(0.0f);
        pEnemy->SetHealth(5000.0f);
        pEnemy->SetIsDead(false);
    }
}


/**
* \brief Renders ship text information.
* \details Renders the ship information on the screen. The ship information
*   includes the amount of energy and the ammo count.
*/
void Level3::RenderShipInfo(void)
{
    const int ammoCount = pPlayer->GetLaserAmmo();
    const float energy = pPlayer->GetHealth();

    wstringstream format;
    format << fixed << setprecision(0) << energy;

    // Creating the energy text
    wstring info = L"Energy: " + format.str() + L"\n";
    // Creating the Ammo count
    info += L"Power: " + to_wstring(ammoCount);

    // Center the text horizontally and vertically
    gfx->GetTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    gfx->GetTextFormat()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    gfx->RenderText(info, screenSize, D2D1::ColorF(255, 255, 255));
}



void Level3::RenderPlanetInfo(PlanetObject* planet)
{
    const int scienceAmount = planet->GetScienceResource();
    const int energyAmount = planet->GetEnergyResource();

    // Creating the energy text
    wstring info = L"Energy: " + to_wstring(energyAmount) + L"\n";
    // Creating the Ammo count
    info += L"Science: " + to_wstring(scienceAmount);

    // Center the text horizontally and vertically
    gfx->GetTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    gfx->GetTextFormat()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    gfx->RenderText(info, screenSize, D2D1::ColorF(255, 106, 0));


    //==---- MENU OPTIONS
    wstring options = L"\n\n";
    options += L"1. Replenish Energy\n";
    options += L"2. Gather Energy\n";
    options += L"3. Leave Orbit";

    // Center the text horizontally and vertically
    gfx->GetTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    gfx->GetTextFormat()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    // The x-position of the text starts 40% of the screen width
    float textPosX = screenSize.right * 0.35f;
    // The y-position of the text starts at the center, offset by 20% of the screen height
    float textPosY = screenSize.right * 0.2f;

    D2D1_RECT_F drawArea = D2D1::RectF(textPosX, textPosY, screenSize.right, screenSize.bottom);
    gfx->RenderText(options, drawArea, D2D1::ColorF(255, 255, 255));
}