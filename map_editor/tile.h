#pragma once
#include <vector>
#include <memory>
struct Tile
{
	int wall = 0;
	double u = 0.2;
};

using TileMap = std::vector<std::vector<Tile>>;