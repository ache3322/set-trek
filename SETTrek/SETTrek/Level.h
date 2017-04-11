/*
* PROJECT		: SETTrek
* FILE			: Level.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	: The header file containing an abstract definition of the Level interface.
*/
#pragma once
#include <vector>
#include <memory>
#include "Graphics.h"
#include "EffectManager.h"
#include "Input.h"
#include "TimerClass.h"
#include "Grid.h"



/**
* \class Level
* \brief The Level is an abstract class that encapsulates the attributes of a game level.
*/
class Level
{
protected:

    enum GameMode
    {
        spaceMode = 0,
        explorationMode = 1
    };

	static Graphics* gfx;		    //!< Reference to the Graphics object
    static D2D1_RECT_F screenSize;	//!< The rectangle area/size of where the object will be drawn 
    static Grid* grid;              //!< The grid for the level
    static GameMode mode;

public:

	static void Init(Graphics * graphics, D2D1_RECT_F screen);
    static void ReInitGrid(void);

	virtual void Load(void) = 0;	            // For loading assets for the game level
	virtual void Unload(void) = 0;				// For unloading assets from the game level
	virtual void Update(void) = 0;				// For updating the game level
	virtual void Render(void) = 0;				// For rendering the game level
	virtual void Process(void) = 0;		// For processing input
};