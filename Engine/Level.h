#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include "Grid.h"

class Level
{
public:
	Level(Grid& grid);
	void drawLevel(Grid& grid);
	std::string getStringFromText(std::ifstream& file);
	int getXPosFromIndex(int index);
	int getYPosFromIndex(int index);
private:
	static constexpr int dimWidth = 8;
	static constexpr int dimHeight = 8;
	std::string levelString;
	std::ifstream levelFile;
	Grid& grid;
};