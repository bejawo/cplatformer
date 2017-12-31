#include "Level.h"

Level::Level(const Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	createArrayFromFile(levelFile);
	int asdf = levelArray[63];

	// Find index of start
	for (int i = 0; i < numTiles; i++)
	{
		if (levelArray[i] == 2)
		{
			startIndex = i;
			break;
		}
			
	}
}

void Level::draw(Graphics& gfx, const Grid& grid) const
{
	for (int i = 0; i < numTiles; i++)
	{
		const int curElem = levelArray[i]; // TODO: levelArray not here
		const Grid::Tile tile = convertIndexToTile(i);

		switch (curElem)
		{
		case 0:
			grid.DrawTile(gfx, tile, Colors::Gray);
			break;
		case 1:
			grid.DrawTile(gfx, tile, Colors::Red);
			break;
		case 2:
			grid.DrawTile(gfx, tile, Colors::Blue);
			break;
		case 3:
			grid.DrawTile(gfx, tile, Colors::Green);
			break;
		}
	}
}

void Level::createArrayFromFile(std::ifstream& file)
{
	// Read file into string
	std::string str;
	str.assign( (std::istreambuf_iterator<char>(file)),
				(std::istreambuf_iterator<char>()) );
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	assert((int) str.length() == numTiles);

	// Convert string to int array
	int arr[numTiles];
	for (int i = 0; i < numTiles; i++)
	{
		arr[i] = charToInt(str.at(i));
	}

	levelArray = arr;
}

int Level::charToInt(char c) const
{
	switch (c)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case 'S':
		return 2;
	case 'F':
		return 3;
	
	default:
		return -1;
	}
}

Grid::Tile Level::convertIndexToTile(int index) const
{
	int x = index % tilesWide;
	int y = index / tilesHigh;
	return {x, y};
}

int Level::convertTileToIndex(Grid::Tile tile) const
{
	return tile.y * tilesWide + tile.x;
}

int Level::intAtTile(const Grid::Tile & tile) const
{
	int index = convertTileToIndex(tile);
	return levelArray[index];
}

int Level::getStartIndex() const
{
	return startIndex;
}

std::string Level::getLevelString() const
{
	return levelString;
}
