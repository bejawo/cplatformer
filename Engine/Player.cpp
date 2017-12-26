#include "Player.h"

Player::Player(Graphics& gfx, Level& level)
	:
	gfx(gfx),
	level(level)
{
	vel.x = 0.0f;
	vel.y = 0.0f;
	
	ResetPosition();
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

void Player::ResetPosition()
{
	int startIndex = level.getStartIndex(); // find start index in levelString
	Grid::Tile startTile = level.getTileFromIndex(startIndex); // convert index to tile position
	// position player in start tile
	pos.x = float(startTile.x * Grid::dimension);
	pos.y = float(startTile.y * Grid::dimension);
	updateGridPosX();
	updateGridPosY();
}

void Player::Update(Keyboard& kbd, float dt)
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
		if (!isJumping && vel.y == 0) // Prevent jumping while falling (will need to change to enable jumping off a moving platform for example)
		{
			isJumping = true;
			//vel.y -= jumpSpeed * dt;
			vel.y = -jumpSpeed * dt;
		}
	}

	if (kbd.KeyIsPressed(82)) // R (ascii decimal value)
	{
		ResetPosition();
	}

	// x movement
	pos.x += vel.x * dt;
	updateGridPosX();
	handleCollisionsX(dt);
	updateGridPosX();

	// y movement

	vel.y += gravity * dt; // TODO: fix gravity - need to fall at same rate
	//vel.y += gravity;
	pos.y += vel.y * dt;
	updateGridPosY();
	handleCollisionsY(dt);
	updateGridPosY();

	clampToGrid(dt);
}

void Player::updateGridPosX()
{
	//assert(pos.x >= 0);
	//assert(pos.x < Level::width);
	left = (int) pos.x / Grid::dimension;
	right = (int) (pos.x + width) / Grid::dimension;
}

void Player::updateGridPosY()
{
	//assert(pos.y >= 0);
	//assert(pos.y < Level::height);
	top = (int) pos.y / Grid::dimension;
	bottom = (int) (pos.y + height) / Grid::dimension;
}

void Player::handleCollisionsX(float dt)
{
	for (int i = top; i <= bottom; i++) // wall on left
	{
		Grid::Tile curTile = { left, i };
		int index = level.getIndexFromTile(curTile);
		char curChar = level.findCharAtIndex(index);
		if (curChar == '1')
		{
			pos.x -= vel.x * dt;
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
			pos.x -= vel.x * dt;
			vel.x = 0.0f;
			return;
		}
	}
	return;
}

void Player::handleCollisionsY(float dt)
{
	for (int i = left; i <= right; i++) // wall on top
	{
		Grid::Tile curTile = { i, top };
		int index = level.getIndexFromTile(curTile);
		char curChar = level.findCharAtIndex(index);
		if (curChar == '1')
		{
			pos.y -= vel.y * dt;
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
			pos.y -= vel.y * dt;
			vel.y = 0.0f;
			isJumping = false;
			return;
		}
	}
	return;
}

void Player::clampToGrid(float dt)
{
	if (pos.x < 0 || pos.x + width > Level::width)
	{
		pos.x -= vel.x * dt;
		vel.x = 0.0f;
	}
	if (pos.y < 0 || pos.y + height > Level::height - 15) // TODO: check collision detection - checking cells too far down? (shouldn't need to offset height here)
	{
		pos.y -= vel.y * dt;
		vel.y = 0.0f;
		isJumping = false;
	}
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
