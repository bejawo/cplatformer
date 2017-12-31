#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "Grid.h"
#include "Vec2.h"

class Level
{
	//struct TileProperties
	//{
	//	bool isWall;
	//	// TODO: add more props here e.g. sprite file, spriteCoords, etc.
	//};

public:
	Level(const Grid& grid);
	void draw(Graphics& gfx, const Grid& grid) const;
	void createArrayFromFile(std::ifstream& file, int* arr);
	Grid::Tile convertIndexToTile(int index) const;
	int convertTileToIndex(Grid::Tile tile) const;
	int intAtTile(const Grid::Tile& tile) const;

	int getStartIndex() const;

private:
	static constexpr int tilesWide = 8;
	static constexpr int tilesHigh = 8;
	static constexpr int numTiles = tilesWide * tilesHigh;
	int levelArray[numTiles];
	std::ifstream levelFile;
	int startIndex = 0;
	const Grid& grid;
/*
	TileProperties tileSet[] = {
		{ false, "sprites.bmp", 0, 0 },
		{ true, "sprites.bmp", 100, 0 },
		{ false, "sprites.bmp", 200, 0 },
		{ false, "sprites.bmp", 0, 100 },
		{ false, "sprites.bmp", 100, 200 }
	};*/

public:
	static constexpr int width = tilesWide * Grid::tileWidth; // Width in pixels
	static constexpr int height = tilesHigh * Grid::tileHeight; // Height in pixels
};