#include "Player.h"

Player::Player(Graphics& gfx, Level& level)
	:
	gfx(gfx),
	level(level)
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
	updateGridPos();
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

	if (kbd.KeyIsPressed(VK_UP))
	{
		vel.y = -3.0f;
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		vel.y = 3.0f;
	}
	else
	{
		vel.y = 0.0f;
	}

	if (isColliding())
	{
		vel.x = 0.0f;
		vel.y = 0.0f;
	}

	pos = pos + vel;

	updateGridPos();
}

void Player::updateGridPos()
{
	top = (int) pos.y / Grid::dimension;
	bottom = (int) (pos.y + height) / Grid::dimension;
	left = (int) pos.x / Grid::dimension;
	right = (int) (pos.x + width) / Grid::dimension;
}

bool Player::isColliding()
{
	Grid::Tile curTile;
	for (int j = top; j <= bottom; j++)
	{
		for (int i = left; i <= right; i++)
		{
			curTile.x = i;
			curTile.y = j;
			int index = level.getIndexFromTile(curTile);
			char curChar = level.findCharAtIndex(index);
			if (curChar == '1')
				return true;
		}
	}
	return false;
}

Vec2 Player::getPos()
{
	return pos;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}
