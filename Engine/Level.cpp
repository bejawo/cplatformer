#include "Level.h"

Level::Level(Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	levelString = getStringFromText(levelFile);
	startIndex = findStartIndex();
}

void Level::drawLevel(Grid & grid)
{
	char curChar;
	int length = (int)levelString.length();
	for (int i = 0; i < length; i++)
	{
		curChar = levelString.at(i);
		Grid::Tile tile = getTileFromIndex(i);

		switch (curChar)
		{
		case '0':
			grid.DrawCell(tile, Colors::Gray);
			break;
		case '1':
			grid.DrawCell(tile, Colors::Red);
			break;
		case 'S':
			grid.DrawCell(tile, Colors::Blue);
			break;
		case 'F':
			grid.DrawCell(tile, Colors::Green);
			break;
		}
	}
}

int Level::findStartIndex()
{
	for (int i = 0; i < numCells; i++)
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

Grid::Tile Level::getTileFromIndex(int index)
{
	int x = index % dimWidth;
	int y = index / dimHeight;
	return {x, y};
}

int Level::getIndexFromTile(Grid::Tile tile)
{
	return tile.y * dimWidth + tile.x;
}

char Level::findCharAtIndex(int index)
{
	return (char) levelString.at(index);
}

int Level::getStartIndex()
{
	return startIndex;
}

std::string Level::getLevelString()
{
	return levelString;
}
