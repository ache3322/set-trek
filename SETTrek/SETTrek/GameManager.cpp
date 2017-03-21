/*
* PROJECT		: SETTrek
* FILE			: GameManager.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/06
* DESCRIPTION	: The CPP file implementation of the GameManager class.
*/
#include "GameManager.h"


Level* GameManager::currentLevel;	// Static variable instance of Level
bool GameManager::IsLoading;		// Using the static boolean


/**
* \brief Initializes the game.
* \details Initialization of the current level.
*/
void GameManager::Init(void)
{
	IsLoading = true;
	currentLevel = NULL;
}


/**
* \brief Loading an initial level.
* \param level - Level* - The level being loaded
* \param size - D2D1_RECT_F - The dimensions of the window screen (client screen)
*/
void GameManager::LoadLevel(Level* level, D2D1_RECT_F size)
{
	IsLoading = true;

	currentLevel = level;
	currentLevel->Load(size);

	IsLoading = false;		// Finished loading the level
}


/**
* \brief Switching new levels.
* \details When switching levels, the current level is unloaded, then
*	the new level is loaded.
* \param level - Level* - The level being loaded
* \param size - D2D1_RECT_F - The dimensions of the window screen (client screen)
*/
void GameManager::SwitchLevel(Level* newLevel, D2D1_RECT_F size)
{
	IsLoading = true;

	currentLevel->Unload();
	currentLevel = newLevel;
	currentLevel->Load(size);

	IsLoading = false;
}


/**
* \brief Unloading the current level.
*/
void GameManager::UnloadLevel(void)
{
	IsLoading = true;

	// Unloading any resources (unloading a level)
	currentLevel->Unload();

	IsLoading = false;
}


/**
* \brief Rendering the game objects inside the level.
* \param void
*/
void GameManager::Render(void)
{
	// To prevent/avoid rendering while the game is loading
	if (IsLoading) {
		return;
	}
	currentLevel->Render();
}


/**
* \brief Updating the game objects inside the level.
* \param void
*/
void GameManager::Update(void)
{
	// To prevent/avoid updating while the game is loading
	if (IsLoading) {
		return;
	}
	currentLevel->Update();
}


/**
* \brief Process the input from the player.
* \details The input from the player could be a mouse-click event.
*/
void GameManager::Process(int mouseX, int mouseY)
{
	if (IsLoading) {
		return;
	}
	currentLevel->Process(mouseX, mouseY);
}