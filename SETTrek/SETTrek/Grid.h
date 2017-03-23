/*
* PROJECT		: SETTrek
* FILE			: Grid.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/03/08
* DESCRIPTION	: Header file containing class definition for the Grid.
*/
#pragma once
#include <time.h>
#include <vector>
#include "Graphics.h"
using namespace std;



//===================
// CONSTANTS
//===================
#define kNumberOfGrid		10
#define kCenterGrid			49
#define kWindowPadding      1.0f

#define kPlanetPadding      5.0f
#define kPlanetSpawnChance  2


//=============================
// GRAPHIC STRUCT DEFINITIONS
//=============================

//===================
// CLASS
//===================
/**
* \class Grid
* \brief The Grid object has methods and functionalities to manipulate a grid.
* \details This grid is used within the game level. It allows for game objects
*	to be mapped to a defined point.
*/
class Grid
{
private:

	float windowWidth;				//!< The width of the window
	float windowHeight;				//!< The height of the window

	float gridWidth;				//!< The width of 1 grid
	float gridHeight;				//!< The height of 1 grid

	int numOfRows;					//!< The number of rows that comprises of the grid
	int numOfCols;					//!< The number of cols that comprises of the grid

	vector<vector2> grid;			//!< Contains the absolute position for the 10 by 10 grid. There are 100 squares in total
	vector<vector2> randGrid;		//!< Contains the grid coordinates of where a random planet may spawn

public:

	//-Constructors
	Grid(void);
	Grid(float windowWidth, float windowHeight);

	//-Destructors
	~Grid(void);

	//-Methods
	void ConstructGrid(void);
	void GenerateRandCoord(void);

	//-Accessors
	float GetWindowWidth(void) const;
	float GetWindowHeight(void) const;

	float GetWidth(void) const;
	float GetHeight(void) const;

	int GetNumRows(void) const;
	int GetNumCols(void) const;

	int GetGridNum(void) const;
	int GetRandCoordSize(void) const;
	
	vector<vector2> GetGrid(void) const;
	vector<vector2> GetRandCoord(void) const;
};