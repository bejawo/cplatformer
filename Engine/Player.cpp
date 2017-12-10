#include "Player.h"

Player::Player(Graphics& gfx, Level& level)
	:
	gfx(gfx)
{
	vel.x = 0.0f;
	vel.y = 0.0f;
	// find S position in levelString
	// convert to grid coords
	// convert to screen position
	int startIndex = level.getStartIndex();
	int x = level.getXPosFromIndex(startIndex);
	int y = level.getYPosFromIndex(startIndex);
	pos.x = float(x * Grid::dimension);
	pos.y = float(y * Grid::dimension);
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

void Player::Update(Keyboard& kbd)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		vel.x = -3.0f;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		vel.x = 3.0f;
	}
	else
	{
		vel.x = 0.0f;
	}
	pos = pos + vel;
}
