#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include <string>
#include "Keyboard.h"
#include <cassert>
#include "ControlInput.h"

class Player
{
public:
	Player(const class Level& level);
	Vec2 getPosFromLevelIndex(int index, int gridWidth, int gridHeight);
	void draw(Graphics& gfx) const;
	void resetPosition(const class Level& level);
	void update(const Keyboard& kbd, const class Level& level, float dt);
	void updateGridPosX();
	void updateGridPosY();

	Vec2 getPos() const;
	void setPosX(float posX); // there may be a better way than setting each of these
	void setPosY(float posY);
	Vec2 getVel() const;
	void setVelX(float velX);
	void setVelY(float velY);
	int getWidth() const;
	int getHeight() const;
	void setIsJumping(bool);

private:
	Vec2 pos; // top-left corner of player rectangle
	Vec2 vel;
	const Color color = Colors::Cyan;
	static constexpr float speed = 3.0f * 60.0f;
	static constexpr float gravity = 20.0f * 60.0f;
	static constexpr float jumpSpeed = 7.0f * 60.0f;
	bool isJumping = false;

public:
	static constexpr int width = 20;
	static constexpr int height = 40;
	int top; // The row player's top edge is in
	int bottom; // The row player's bottom edge is in
	int left; // The column player's left edge is in
	int right; // The column player's right edge is in
};