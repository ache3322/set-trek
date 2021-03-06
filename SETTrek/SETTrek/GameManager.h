/*
* PROJECT		: SETTrek
* FILE			: GameManager.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/06
* DESCRIPTION	: The GameManager is our specialized entry point.
*			Think if the GameManager class as the specialized 'Main'
*			that will be the top-parent of the game objects, inputs,
*			outpus, updating and rendering.
*/
#pragma once
#include "Level.h"


/**
* \class GameManager
* \brief The GameManager (GameController) will initializes, renders, and updates the game.
* \details The GameManager class is implemented as a Singleton. The purpose of this
*	class is to run the game. The manager initializes all the resources required (the levels),
*	renders shapes, and updates the game.
*/
class GameManager
{
private:

	GameManager() {}				//!< A private constructor - allows for Singleton instance
	static Level* currentLevel;		//!< The current level that is loaded

public:

	static bool IsLoading;			//!< The current state of the game - is it loading?
    static bool IsPaused;

	static void LoadLevel(Level* level);
	static void SwitchLevel(Level* newLevel);
	static void UnloadLevel(void);

	static void Init(void);
	static void Render(void);
	static void Update(void);
	static void Process(void);
};