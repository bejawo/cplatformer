#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Level.h"
#include <string>
#include "Keyboard.h"

class Player
{
public:
	Player(Graphics& gfx, Level& level);
	Vec2 getPosFromLevelIndex(int index, int gridWidth, int gridHeight);
	void drawPlayer();
	void Update(Keyboard& kbd);
	void updateGridPos();
	bool isColliding();

	Vec2 getPos();
	int getWidth();
	int getHeight();
private:
	Vec2 pos;
	Vec2 vel;
	static constexpr int width = 20;
	static constexpr int height = 40;
	Color color = Colors::Cyan;
	Graphics& gfx;
	Level& level;
public:
	int top;
	int bottom;
	int left;
	int right;
};