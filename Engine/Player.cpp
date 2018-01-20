#include "Player.h"
#include "Level.h"

Player::Player(const class Level& level, Surface& s)
	:
	playerSprite(s)
{
	vel.x = 0.0f;
	vel.y = 0.0f;
	
	resetPosition(level);
}

Vec2 Player::getPosFromLevelIndex(int index, int gridWidth, int gridHeight)
{
	int x = index % gridWidth;
	int y = index / gridHeight;
	return Vec2((float)x, (float)y);
}

void Player::draw(Graphics& gfx) const
{
	gfx.DrawSprite((int)pos.x, (int)pos.y, playerSprite);
}

void Player::resetPosition(const Level& level)
{
	int startIndex = level.getStartIndex();
	Grid::Tile startTile = level.convertIndexToTile(startIndex);
	pos.x = float(startTile.x * Grid::tileWidth);
	pos.y = float(startTile.y * Grid::tileHeight);
	updateGridPosX();
	updateGridPosY();
}

void Player::update(const Keyboard& kbd, const Level& level, float dt)
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
		resetPosition(level);
	}

	// x movement
	pos.x += vel.x * dt;
	updateGridPosX();
	level.handleCollisionsX(*this, dt);
	updateGridPosX();

	// y movement
	vel.y += gravity * dt;
	pos.y += vel.y * dt;
	updateGridPosY();
	level.handleCollisionsY(*this, dt);
	updateGridPosY();

	level.clampToGrid(*this, dt);
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

Vec2 Player::getPos() const
{
	return pos;
}

void Player::setPosX(float posX)
{
	pos.x = posX;
}

void Player::setPosY(float posY)
{
	pos.y = posY;
}

Vec2 Player::getVel() const
{
	return vel;
}

void Player::setVelX(float velX)
{
	vel.x = velX;
}

void Player::setVelY(float velY)
{
	vel.y = velY;
}

void Player::setIsJumping(bool b)
{
	isJumping = b;
}
