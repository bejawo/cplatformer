#pragma once

#include "Colors.h"
#include "Graphics.h"

class Grid
{
public:
	struct Tile
	{
		int x;
		int y;
	};

public:
	void DrawTile(Graphics& gfx, Grid::Tile tile, Color c) const
	{
		gfx.DrawRect(tile.x * tileWidth, tile.y * tileHeight, tileWidth, tileHeight, c);
	}

public:
	static constexpr int tileHeight = 60;
	static constexpr int tileWidth = 60;
};