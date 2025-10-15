#pragma once
#include "wall_box.h"

#include <vector>
#include <memory>
struct Tile
{
	std::shared_ptr<WallBox> wall_box = nullptr;
	int wall = 0;
	int size = 32;
};

using TileMap = std::vector<std::vector<Tile>>;