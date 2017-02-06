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


/*
* \class GameManager
* \brief
*/
class GameManager
{
private:



public:

	GameManager();
	~GameManager();

	bool InitGame(void);
};