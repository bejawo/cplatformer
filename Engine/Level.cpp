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

int Level::intAtTile(const Grid::Tile& tile) const
{
	int index = convertTileToIndex(tile);
	return levelArray[index];
}

void Level::handleCollisionsX(Player& player, float dt) const
{
	Vec2 pos = player.getPos();
	Vec2 vel = player.getVel();

	for (int i = player.top; i <= player.bottom; i++) // wall on left
	{
		int curInt = intAtTile({ player.left, i });
		if (curInt == 1)
		{
			player.setPosX(pos.x - vel.x * dt);
			player.setVelX(0.0f);
			return;
		}
	}
	for (int i = player.top; i <= player.bottom; i++) // wall on right
	{
		int curInt = intAtTile({ player.right, i });
		if (curInt == 1)
		{
			player.setPosX(pos.x - vel.x * dt);
			player.setVelX(0.0f);
			return;
		}
	}
	return;
}

void Level::handleCollisionsY(Player& player, float dt) const
{
	Vec2 pos = player.getPos();
	Vec2 vel = player.getVel();

	for (int i = player.left; i <= player.right; i++) // wall on top
	{
		int curInt = intAtTile({ i, player.top });
		if (curInt == 1)
		{
			player.setPosY(pos.y - vel.y * dt);
			player.setVelY(0.0f);
			return;
		}
	}
	for (int i = player.left; i <= player.right; i++) // wall on bottom
	{
		int curInt = intAtTile({ i, player.bottom });
		if (curInt == 1)
		{
			player.setPosY(pos.y - vel.y * dt);
			player.setVelY(0.0f);
			player.setIsJumping(false);
			return;
		}
	}
	return;
}

void Level::clampToGrid(Player& player, float dt) const
{
	Vec2 pos = player.getPos();
	Vec2 vel = player.getVel();

	// Left and right
	if (pos.x < 0 || pos.x + player.width > Level::width)
	{
		player.setPosX(pos.x - vel.x * dt);
		player.setVelX(0.0f);
	}
	// Top and bottom
	if (pos.y < 0 || pos.y + player.height > Level::height - 15) // TODO: check collision detection - checking tiles too far down? (shouldn't need to offset height here)
	{
		player.setPosY(pos.y - vel.y * dt);
		player.setVelY(0.0f);
		player.setIsJumping(false);
	}
}


int Level::getStartIndex() const
{
	return startIndex;
}