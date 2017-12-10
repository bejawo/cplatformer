#include "Level.h"

Level::Level(Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	levelString = getStringFromText(levelFile);
}

void Level::drawLevel(Grid & grid)
{
	char curChar;
	int length = levelString.length();
	for (int i = 0; i < length; i++)
	{
		curChar = levelString.at(i);
		int x = getXPosFromIndex(i);
		int y = getYPosFromIndex(i);

		switch (curChar)
		{
		case '0':
			grid.DrawCell(x, y, Colors::Gray);
			break;
		case '1':
			grid.DrawCell(x, y, Colors::Red);
			break;
		case 'S':
			grid.DrawCell(x, y, Colors::Blue);
			break;
		case 'F':
			grid.DrawCell(x, y, Colors::Green);
			break;
		}
			
	}
}

std::string Level::getStringFromText(std::ifstream& file)
{
	std::string str;
	str.assign( (std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()) );
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	return str;
}

int Level::getXPosFromIndex(int index)
{
	return index % dimWidth;
}

int Level::getYPosFromIndex(int index)
{
	return index / dimHeight;
}
