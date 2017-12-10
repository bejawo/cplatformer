#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "Grid.h"
#include "Vec2.h"

class Level
{
public:
	Level(Grid& grid);
	void drawLevel(Grid& grid);
	int findStartIndex();
	std::string getStringFromText(std::ifstream& file);
	int getXPosFromIndex(int index);
	int getYPosFromIndex(int index);
	int getIndexFromTile(Grid::Tile);
	char findCharAtIndex(int index);

	int getStartIndex();
	std::string getLevelString();
private:
	static constexpr int dimWidth = 8;
	static constexpr int dimHeight = 8;
	static constexpr int numCells = dimWidth * dimHeight;
	std::string levelString;
	std::ifstream levelFile;
	int startIndex;
	Grid& grid;
};