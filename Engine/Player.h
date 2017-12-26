#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Level.h"
#include <string>
#include "Keyboard.h"
#include <cassert>

class Player
{
public:
	Player(Graphics& gfx, Level& level);
	Vec2 getPosFromLevelIndex(int index, int gridWidth, int gridHeight);
	void drawPlayer();
	void ResetPosition();
	void Update(Keyboard& kbd, float dt);
	void updateGridPosX();
	void updateGridPosY();
	void handleCollisionsX(float dt);
	void handleCollisionsY(float dt);
	void clampToGrid(float dt);

	Vec2 getPos();
	int getWidth();
	int getHeight();

private:
	Vec2 pos; // top-left corner of player rectangle
	Vec2 vel;
	static constexpr float speed = 3.0f * 60.0f;
	static constexpr int width = 20;
	static constexpr int height = 40;
	Color color = Colors::Cyan;
	Graphics& gfx;
	Level& level;
	static constexpr float gravity = 20.0f * 60.0f;
	bool isJumping = false;
	static constexpr float jumpSpeed = 7.0f * 60.0f;

public:
	int top; // The row player's top edge is in
	int bottom; // The row player's bottom edge is in
	int left; // The column player's left edge is in
	int right; // The column player's right edge is in
};