#include "Player.h"

Player::Player(const Level& level)
	:
	level(level)
{
	vel.x = 0.0f;
	vel.y = 0.0f;
	
	resetPosition();
}

Vec2 Player::getPosFromLevelIndex(int index, int gridWidth, int gridHeight)
{
	int x = index % gridWidth;
	int y = index / gridHeight;
	return Vec2((float)x, (float)y);
}

void Player::draw(Graphics& gfx) const
{
	gfx.DrawRect((int)pos.x, (int)pos.y, width, height, color);
}

void Player::resetPosition()
{
	int startIndex = level.getStartIndex();
	Grid::Tile startTile = level.convertIndexToTile(startIndex);
	pos.x = float(startTile.x * Grid::tileWidth);
	pos.y = float(startTile.y * Grid::tileHeight);
	updateGridPosX();
	updateGridPosY();
}

void Player::update(const Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(ControlInput::moveLeft))
	{
		vel.x = -speed;
	}
	else if (kbd.KeyIsPressed(ControlInput::moveRight))
	{
		vel.x = speed;
	}
	else
	{
		vel.x = 0.0f;
	}

	if (kbd.KeyIsPressed(ControlInput::jump))
	{
		if (!isJumping && vel.y == 0) // Prevent jumping while falling (will need to change to enable jumping off a moving platform for example)
		{
			isJumping = true;
			vel.y = -jumpSpeed;
		}
	}

	if (kbd.KeyIsPressed(ControlInput::resetPosition))
	{
		resetPosition();
	}

	// x movement
	pos.x += vel.x * dt;
	updateGridPosX();
	handleCollisionsX(dt);
	updateGridPosX();

	// y movement
	vel.y += gravity * dt;
	pos.y += vel.y * dt;
	updateGridPosY();
	handleCollisionsY(dt);
	updateGridPosY();

	clampToGrid(dt);
}

void Player::updateGridPosX()
{
	assert(pos.x >= -10);
	assert(pos.x < Level::width + 10);
	left = (int) pos.x / Grid::tileWidth;
	right = (int) (pos.x + width) / Grid::tileWidth;
}

void Player::updateGridPosY()
{
	assert(pos.y >= -10);
	assert(pos.y < Level::height + 10);
	top = (int) pos.y / Grid::tileHeight;
	bottom = (int) (pos.y + height) / Grid::tileHeight;
}

void Player::handleCollisionsX(float dt)
{
	for (int i = top; i <= bottom; i++) // wall on left
	{
		Grid::Tile curTile = { left, i };
		int index = level.convertTileToIndex(curTile);
		char curChar = level.charAtIndex(index);
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
		int index = level.convertTileToIndex(curTile);
		char curChar = level.charAtIndex(index);
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
		int index = level.convertTileToIndex(curTile);
		char curChar = level.charAtIndex(index);
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
		int index = level.convertTileToIndex(curTile);
		char curChar = level.charAtIndex(index);
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
	if (pos.y < 0 || pos.y + height > Level::height - 15) // TODO: check collision detection - checking tiles too far down? (shouldn't need to offset height here)
	{
		pos.y -= vel.y * dt;
		vel.y = 0.0f;
		isJumping = false;
	}
}

Vec2 Player::getPos() const
{
	return pos;
}

int Player::getWidth() const
{
	return width;
}

int Player::getHeight() const
{
	return height;
}
