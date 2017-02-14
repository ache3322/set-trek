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
* \brief
* \details
* \param
*/
void GameManager::LoadLevel(Level* level)
{
	IsLoading = true;

	currentLevel = level;
	currentLevel->Load();

	IsLoading = false;		// Finished loading the level
}


/**
* \brief
* \details
* \param
* \return
*/
void GameManager::Render(void)
{
	// To prevent/avoid rendering while the game is loading
	if (IsLoading) {
		return;
	}
}


/**
* \brief
* \details
* \param
* \return
*/
void GameManager::Update(void)
{
	// To prevent/avoid updating while the game is loading
	if (IsLoading) {
		return;
	}
}