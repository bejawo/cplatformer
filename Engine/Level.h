#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "Grid.h"
#include "Vec2.h"

class Level
{
public:
	Level(const Grid& grid);
	void draw(Graphics& gfx, const Grid& grid) const;
	std::string readFileIntoString(std::ifstream& file);
	Grid::Tile convertIndexToTile(int index) const;
	int convertTileToIndex(Grid::Tile tile) const;
	char charAtIndex(int index) const;

	int getStartIndex() const;
	std::string getLevelString() const;

private:
	static constexpr int tilesWide = 8;
	static constexpr int tilesHigh = 8;
	static constexpr int numTiles = tilesWide * tilesHigh;
	std::string levelString;
	std::ifstream levelFile;
	int startIndex = 0;
	const Grid& grid;

public:
	static constexpr int width = tilesWide * Grid::tileWidth; // Width in pixels
	static constexpr int height = tilesHigh * Grid::tileHeight; // Height in pixels
};