#include "Grid.h"

Grid::Grid(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Grid::DrawCell(int x, int y, Color c)
{
	gfx.DrawRect(x * dimension, y * dimension, dimension, dimension, c);
}

Grid::Tile Grid::findTileFromPixel(int x, int y)
{
	int tileX = x / dimension;
	int tileY = y / dimension;
	return {tileX, tileY};
}
