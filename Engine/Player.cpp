#include "Player.h"

Player::Player(Graphics& gfx, Level& level)
	:
	gfx(gfx)
{
	// find S position in levelString
	// convert to grid coords
	// convert to screen position
	int startIndex = level.getStartIndex();
	int x = level.getXPosFromIndex(startIndex);
	int y = level.getYPosFromIndex(startIndex);
	pos = { float(x * Grid::dimension), float(y * Grid::dimension) };
}

Vec2 Player::getPosFromLevelIndex(int index, int gridWidth, int gridHeight)
{
	int x = index % gridWidth;
	int y = index / gridHeight;
	return Vec2((float)x, (float)y);
}

void Player::drawPlayer()
{
	gfx.DrawRect((int)pos.x, (int)pos.y, width, height, color);
}
