#include "Level.h"

Level::Level(Grid& grid)
	:
	grid(grid)
{
	levelString = getStringFromText();
}

void Level::drawLevel(Grid & grid)
{
	// TODO: draw level from string
}

char Level::getCharAtIndex(int index)
{

	return 0;
}

std::string Level::getStringFromText()
{
	std::ifstream file("level.txt");
	std::string str;
	str.assign( (std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()) );
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	return str;
}
