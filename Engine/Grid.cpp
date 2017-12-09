#include "Grid.h"

Grid::Grid(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Grid::DrawCell(int x, int y, Color c)
{
	gfx.DrawRect(x, y, dimension, dimension, c);
}
