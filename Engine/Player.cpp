#include "Player.h"

Player::Player(Graphics& gfx, Level& level)
	:
	gfx(gfx),
	level(level)
{
	vel.x = 0.0f;
	vel.y = 0.0f;
	
	int startIndex = level.getStartIndex(); // find start index in levelString
	Grid::Tile startTile = level.getTileFromIndex(startIndex); // convert index to tile position
	// position player in start tile
	pos.x = float(startTile.x * Grid::dimension);
	pos.y = float(startTile.y * Grid::dimension);
	updateGridPosX();
	updateGridPosY();
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
		vel.x = -speed;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		vel.x = speed;
	}
	else
	{
		vel.x = 0.0f;
	}

	if (kbd.KeyIsPressed(VK_UP))
	{
		if (!isJumping)
		{
			isJumping = true;
			vel.y += -12.0f;
		}
	}

	// x movement
	pos.x += vel.x;
	updateGridPosX();
	handleCollisionsX();
	updateGridPosX();

	// y movement
	vel.y += gravity;
	pos.y += vel.y;
	updateGridPosY();
	handleCollisionsY();
	updateGridPosY();
}

void Player::updateGridPosX()
{
	left = (int) pos.x / Grid::dimension;
	right = (int) (pos.x + width) / Grid::dimension;
}

void Player::updateGridPosY()
{
	top = (int) pos.y / Grid::dimension;
	bottom = (int) (pos.y + height) / Grid::dimension;
}

void Player::handleCollisionsX()
{
	for (int i = top; i <= bottom; i++) // wall on left
	{
		Grid::Tile curTile = { left, i };
		int index = level.getIndexFromTile(curTile);
		char curChar = level.findCharAtIndex(index);
		if (curChar == '1')
		{
			pos.x -= vel.x;
			vel.x = 0.0f;
			return;
		}
	}
	for (int i = top; i <= bottom; i++) // wall on right
	{
		Grid::Tile curTile = { right, i };
		int index = level.getIndexFromTile(curTile);
		char curChar = level.findCharAtIndex(index);
		if (curChar == '1')
		{
			pos.x -= vel.x;
			vel.x = 0.0f;
			return;
		}
	}
	return;
}

void Player::handleCollisionsY()
{
	for (int i = left; i <= right; i++) // wall on top
	{
		Grid::Tile curTile = { i, top };
		int index = level.getIndexFromTile(curTile);
		char curChar = level.findCharAtIndex(index);
		if (curChar == '1')
		{
			pos.y -= vel.y;
			vel.y = 0.0f;
			return;
		}
	}
	for (int i = left; i <= right; i++) // wall on bottom
	{
		Grid::Tile curTile = { i, bottom };
		int index = level.getIndexFromTile(curTile);
		char curChar = level.findCharAtIndex(index);
		if (curChar == '1')
		{
			pos.y -= vel.y;
			vel.y = 0.0f;
			isJumping = false;
			return;
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
