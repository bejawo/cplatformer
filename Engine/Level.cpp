#include "Level.h"

Level::Level(const Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	levelString = getStringFromText(levelFile);
	startIndex = findStartIndex();
}

void Level::drawLevel(const Grid& grid)
{
	const int length = (int) levelString.length();

	for (int i = 0; i < length; i++)
	{
		const char curChar = levelString.at(i);
		const Grid::Tile tile = getTileFromIndex(i);

		switch (curChar)
		{
		case '0':
			grid.DrawTile(tile, Colors::Gray);
			break;
		case '1':
			grid.DrawTile(tile, Colors::Red);
			break;
		case 'S':
			grid.DrawTile(tile, Colors::Blue);
			break;
		case 'F':
			grid.DrawTile(tile, Colors::Green);
			break;
		}
	}
}

int Level::findStartIndex() const
{
	for (int i = 0; i < numTiles; i++)
	{
		if (levelString.at(i) == 'S')
			return i;
	}
	return -1;
}

std::string Level::getStringFromText(std::ifstream& file)
{
	std::string str;
	str.assign( (std::istreambuf_iterator<char>(file)),
				(std::istreambuf_iterator<char>()) );
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	return str;
}

Grid::Tile Level::getTileFromIndex(int index) const
{
	int x = index % tilesPerRow;
	int y = index / tilesPerColumn;
	return {x, y};
}

int Level::getIndexFromTile(Grid::Tile tile) const
{
	return tile.y * tilesPerRow + tile.x;
}

char Level::findCharAtIndex(int index) const
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
