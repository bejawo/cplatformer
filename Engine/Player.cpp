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
	Grid::Tile startTile = level.getTileFromIndex(startIndex);
	pos.x = float(startTile.x * Grid::dimension);
	pos.y = float(startTile.y * Grid::dimension);
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

	Vec2 oldPos = pos;
	pos = pos + vel;

	handleCollisions(oldPos);

	updateGridPos();
}

void Player::updateGridPos()
{
	top = (int) pos.y / Grid::dimension;
	bottom = (int) (pos.y + height) / Grid::dimension;
	left = (int) pos.x / Grid::dimension;
	right = (int) (pos.x + width) / Grid::dimension;
}

void Player::handleCollisions(Vec2& oldPos)
{
	// Check whether any tiles the player is touching are walls
	Grid::Tile curTile;
	for (int j = top; j <= bottom; j++) // TODO: only check outer tiles? corner tiles?
	{
		for (int i = left; i <= right; i++)
		{
			curTile.x = i;
			curTile.y = j;
			int index = level.getIndexFromTile(curTile);
			char curChar = level.findCharAtIndex(index);
			if (curChar == '1')
			{
				//if (curTile.x == left)
				//{
				//	// left
				//	pos.x++;
				//}
				//else if (curTile.x == right)
				//{
				//	// right
				//	pos.x--;
				//}
				//if (curTile.y == top)
				//{
				//	// top
				//	pos.y++;
				//}
				//else if (curTile.y == bottom)
				//{
				//	// bottom
				//	pos.y--;
				//}
				pos = oldPos;
			}
		}
	}
	return;
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
