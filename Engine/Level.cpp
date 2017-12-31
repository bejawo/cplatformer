#include "Level.h"

Level::Level(const Grid& grid)
	:
	grid(grid)
{
	levelFile.open("level.txt");
	createArrayFromFile(levelFile, levelArray);

	// Find index of start
	for (int i = 0; i < numTiles; i++)
	{
		if (levelArray[i] == TileType::Start)
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
		const Grid::Tile tile = convertIndexToTile(i);

		switch (levelArray[i])
		{
		case TileType::Empty:
			grid.DrawTile(gfx, tile, Colors::Gray);
			break;
		case TileType::Wall:
			grid.DrawTile(gfx, tile, Colors::Red);
			break;
		case TileType::Start:
			grid.DrawTile(gfx, tile, Colors::Blue);
			break;
		case TileType::Finish:
			grid.DrawTile(gfx, tile, Colors::Green);
			break;
		case TileType::Unknown:
			grid.DrawTile(gfx, tile, Colors::Magenta);
			break;
		}
	}
}

void Level::createArrayFromFile(std::ifstream& file, TileType* arr)
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
		TileType tileType;
		switch (str.at(i))
		{
		case '0':
			tileType = TileType::Empty;
			break;
		case '1':
			tileType = TileType::Wall;
			break;
		case 'S':
			tileType = TileType::Start;
			break;
		case 'F':
			tileType = TileType::Finish;
			break;

		default:
			tileType = TileType::Unknown;
		}

		arr[i] = tileType;
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

Level::TileType Level::typeOfTile(const Grid::Tile& tile) const
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
		TileType tileType = typeOfTile({ player.left, i });
		if (tileType == TileType::Wall)
		{
			player.setPosX(pos.x - vel.x * dt);
			player.setVelX(0.0f);
			return;
		}
	}
	for (int i = player.top; i <= player.bottom; i++) // wall on right
	{
		TileType tileType = typeOfTile({ player.right, i });
		if (tileType == TileType::Wall)
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
		TileType tileType = typeOfTile({ i, player.top });
		if (tileType == TileType::Wall)
		{
			player.setPosY(pos.y - vel.y * dt);
			player.setVelY(0.0f);
			return;
		}
	}
	for (int i = player.left; i <= player.right; i++) // wall on bottom
	{
		TileType tileType = typeOfTile({ i, player.bottom });
		if (tileType == TileType::Wall)
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