#include "Grid.h"

Grid::Grid(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Grid::DrawCell(Grid::Tile tile, Color c)
{
	gfx.DrawRect(tile.x * dimension, tile.y * dimension, dimension, dimension, c);
}

Grid::Tile Grid::findTileFromPixel(int x, int y)
{
	int tileX = x / dimension;
	int tileY = y / dimension;
	return {tileX, tileY};
}
