#pragma once

#include "Colors.h"
#include "Graphics.h"

class Grid
{
public:
	Grid(Graphics& gfx);
	void DrawCell(int x, int y, Color c);
	int findCellPixelPos(int x, int y);

private:
	static constexpr int width = 20;
	static constexpr int height = 20;
	Graphics& gfx;
public:
	static constexpr int dimension = 60;
};