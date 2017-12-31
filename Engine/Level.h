#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "Grid.h"
#include "Vec2.h"
#include "Player.h"

class Level
{
public:
	enum class TileType
	{
		Unknown,
		Empty,
		Wall,
		Start,
		Finish
	};

public:
	Level(const Grid& grid);
	void draw(Graphics& gfx, const Grid& grid) const;
	void createArrayFromFile(std::ifstream& file, TileType* arr);
	Grid::Tile convertIndexToTile(int index) const;
	int convertTileToIndex(Grid::Tile tile) const;
	TileType typeOfTile(const Grid::Tile& tile) const;
	// Collisions
	void handleCollisionsX(Player& player, float dt) const;
	void handleCollisionsY(Player& player, float dt) const;
	void clampToGrid(Player& player, float dt) const;

	int getStartIndex() const;

private:
	static constexpr int tilesWide = 8;
	static constexpr int tilesHigh = 8;
	static constexpr int numTiles = tilesWide * tilesHigh;
	TileType levelArray[numTiles];
	std::ifstream levelFile;
	int startIndex;
	const Grid& grid;

public:
	static constexpr int width = tilesWide * Grid::tileWidth; // Width in pixels
	static constexpr int height = tilesHigh * Grid::tileHeight; // Height in pixels
};