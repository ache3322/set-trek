/*
* PROJECT		: SETTrek
* FILE			: Level.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/14
* DESCRIPTION	:
*/
#pragma once
#include "Level.h"




/**
* \class Level1
* \brief This is the first level.
* \details The level will contain all the associated logic and assets
*	associated for the initial level.
*/
class Level1 : public Level
{
private:



public:

	void Load(void) override;		// For loading assets for the game level
	void Unload(void) override;		// For unloading assets from the game level
	void Update(void) override;		// For updating the game level
	void Render(void) override;		// For rendering the game level
};