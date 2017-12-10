#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "Grid.h"

class Level
{
public:
	Level(Grid& grid);
	void drawLevel(Grid& grid);
	int findStartIndex();
	std::string getStringFromText(std::ifstream& file);
	int getXPosFromIndex(int index);
	int getYPosFromIndex(int index);
	std::string& getLevelString();

	int getStartIndex();
private:
	static constexpr int dimWidth = 8;
	static constexpr int dimHeight = 8;
	static constexpr int numCells = dimWidth * dimHeight;
	std::string levelString;
	std::ifstream levelFile;
	int startIndex;
	Grid& grid;
};