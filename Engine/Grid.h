#pragma once

#include "Colors.h"
#include "Graphics.h"

class Grid
{
public:
	Grid(Graphics& gfx);
	void DrawCell(int x, int y, Color c);

private:
	static constexpr int width = 20;
	static constexpr int height = 20;
	static constexpr int dimension = 20;
	Graphics& gfx;
};