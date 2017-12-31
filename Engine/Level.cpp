#include "Level.h"

Level::Level(const Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	createArrayFromFile(levelFile, levelArray);
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
		const int curElem = levelArray[i];
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

void Level::createArrayFromFile(std::ifstream& file, int* arr)
{
	// Read file into string
	std::string str;
	str.assign( (std::istreambuf_iterator<char>(file)),
				(std::istreambuf_iterator<char>()) );
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	assert((int) str.length() == numTiles);

	// Convert string to int array
	for (int i = 0; i < numTiles; i++)
	{
		int c;
		switch (str.at(i))
		{
		case '0':
			c = 0;
			break;
		case '1':
			c = 1;
			break;
		case 'S':
			c = 2;
			break;
		case 'F':
			c = 3;
			break;

		default:
			c = -1;
		}

		arr[i] = c;
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