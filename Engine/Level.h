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
	void drawLevel(const Grid& grid);
	int findStartIndex() const;
	std::string getStringFromText(std::ifstream& file);
	Grid::Tile getTileFromIndex(int index) const;
	int getIndexFromTile(Grid::Tile tile) const;
	char findCharAtIndex(int index) const;

	int getStartIndex() const;
	std::string getLevelString() const;

private:
	static constexpr int tilesPerRow = 8;
	static constexpr int tilesPerColumn = 8;
	static constexpr int numTiles = tilesPerRow * tilesPerColumn;
	std::string levelString;
	std::ifstream levelFile;
	int startIndex;
	const Grid& grid;

public:
	static constexpr int width = tilesPerRow * Grid::dimension; // Width in pixels
	static constexpr int height = tilesPerColumn * Grid::dimension; // Height in pixels
};