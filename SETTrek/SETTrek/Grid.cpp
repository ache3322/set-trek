/*
* PROJECT		: SETTrek
* FILE			: Grid.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/03/08
* DESCRIPTION	: CPP file containing implementation for the Grid class.
*/
#include "Grid.h"



/**
* \brief The default Grid constructor.
* \param None
* \return None
*/
Grid::Grid(void)
{
	windowWidth = 0.0f;
	windowHeight = 0.0f;
	gridWidth = 0.0f;
	gridHeight = 0.0f;

	numOfRows = 0;
	numOfCols = 0;
}


/**
* \brief A Grid constructor taking 2 parameters.
* \details The 2 parameters are floats for window sizes.
* \param width - float - The width of the window
* \param height - float - The height of the window
* \return None
*/
Grid::Grid(float width, float height)
{
	windowWidth = width;
	windowHeight = height;
	gridWidth = windowWidth / kNumberOfGrid;
	gridHeight = windowHeight / kNumberOfGrid;

	numOfRows = 0;
	numOfCols = 0;
}


/**
* \brief Destructor for the Grid object.
*/
Grid::~Grid(void)
{
}


/**
* \brief Construct the space grid.
* \details The calculation for the space grids are
*       found by each row and column. Initially the an
*       individual grid with and grid height is found.
*/
void Grid::ConstructGrid(void)
{
	int row = 0;
	int col = 0;

	for (row = 0; row < kNumberOfGrid; ++row)
	{
		for (col = 0; col < kNumberOfGrid; ++col)
		{
			// The pair takes in pair coordinates: (x, y), (col, row)
			// The col is along the X-axis
			// The row is along the Y-axis
			vector2 vCoord = { col*  gridWidth, row * gridHeight };
			grid.push_back(vCoord);
		}
	}
}


/**
* \brief Generate random coordinates for Planet spawning.
* \details The grid points are chosen at random. There is an
*       approximately 5% chance that a Planet will spawn at the grid point.
*/
void Grid::GenerateRandCoord(void)
{
	bool isSpawn = false;
	randGrid.clear();

	// For each grid position, calculate the chance
	// for a planet to spawn. There is a 1 in 20 (5%) chance
	// that a planet will spawn...
	for (int i = 0; i < grid.size(); ++i)
	{
        if (i != kPlayerSpawn)
        {
            isSpawn = (rand() % 100) < kPlanetSpawnChance;

            if (isSpawn)
            {
                // These are the chosen grid positions 
                // where a planet is going to be drawn at
                vector2 vCoord = { grid[i].x, grid[i].y };
                randGrid.push_back(vCoord);

                isSpawn = false;
            }
        }
	}
}


//-Accessors
float Grid::GetWindowWidth(void) const {
	return windowWidth;
}
float Grid::GetWindowHeight(void) const {
	return windowHeight;
}

float Grid::GetWidth(void) const {
	return gridWidth;
}
float Grid::GetHeight(void) const {
	return gridHeight;
}

int Grid::GetNumRows(void) const {
	return numOfRows;
}
int Grid::GetNumCols(void) const {
	return numOfCols;
}

int Grid::GetGridNum(void) const {
	return (int)grid.size();
}
int Grid::GetRandCoordSize(void) const {
	return (int)randGrid.size();
}

vector<vector2> Grid::GetGrid(void) const {
	return grid;
}
vector<vector2> Grid::GetRandCoord(void) const {
	return randGrid;
}