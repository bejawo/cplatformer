#include "Level.h"

Level::Level(const Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	levelString = readFileIntoString(levelFile);

	// Find index of start
	for (int i = 0; i < numTiles; i++)
	{
		if (levelString.at(i) == 'S')
			startIndex = i;
	}
}

void Level::draw(Graphics& gfx, const Grid& grid) const
{
	for (int i = 0; i < numTiles; i++)
	{
		const char curChar = charAtIndex(i);
		const Grid::Tile tile = convertIndexToTile(i);

		switch (curChar)
		{
		case '0':
			grid.DrawTile(gfx, tile, Colors::Gray);
			break;
		case '1':
			grid.DrawTile(gfx, tile, Colors::Red);
			break;
		case 'S':
			grid.DrawTile(gfx, tile, Colors::Blue);
			break;
		case 'F':
			grid.DrawTile(gfx, tile, Colors::Green);
			break;
		}
	}
}

std::string Level::readFileIntoString(std::ifstream& file)
{
	std::string str;
	str.assign( (std::istreambuf_iterator<char>(file)),
				(std::istreambuf_iterator<char>()) );
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	return str;
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

char Level::charAtIndex(int index) const
{
	return (char) levelString.at(index);
}

int Level::getStartIndex() const
{
	return startIndex;
}

std::string Level::getLevelString() const
{
	return levelString;
}
