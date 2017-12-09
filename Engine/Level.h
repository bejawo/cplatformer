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
	char getCharAtIndex(int index);
	std::string getStringFromText();
private:
	static constexpr int width = 8;
	static constexpr int height = 8;
	std::string levelString;
	Grid& grid;
};