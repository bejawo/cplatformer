#pragma once

#include "Grid.h"

class Level
{
public:
	Level(Grid& grid);
	void drawLevel(Grid& grid);
private:
	static constexpr int width = 20;
	static constexpr int height = 20;
	char levelArray[height];
	Grid& grid;
};