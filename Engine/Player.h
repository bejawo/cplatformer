#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Level.h"
#include <string>

class Player
{
public:
	Player(Graphics& gfx, Level& level);
	Vec2 getPosFromLevelIndex(int index, int gridWidth, int gridHeight);
	void drawPlayer();
private:
	Vec2 pos;
	Vec2 vel;
	static constexpr int width = 20;
	static constexpr int height = 40;
	static constexpr Color color = Colors::Cyan;
	Graphics& gfx;
};