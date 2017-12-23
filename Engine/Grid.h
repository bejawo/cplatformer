#pragma once

#include "Colors.h"
#include "Graphics.h"

class Grid
{
public:
	struct Tile
	{
		int x;
		int y;
	};
public:
	Grid(Graphics& gfx);
	void DrawCell(Grid::Tile tile, Color c);
	Tile findTileFromPixel(int x, int y);

private:
	Graphics& gfx;
public:
	static constexpr int dimension = 60; // tile size in pixels
};