#pragma once
#include "manager.h"
#include "map.h"

class MapManager:public Manager<MapManager>
{
	friend class Manager<MapManager>;
public:
	void on_update(double delta)
	{

	}

protected:
	MapManager();
	~MapManager();

	void create_wall_map()
	{
		TileMap& tile_map = map.get_tile_map();
		std::vector<int> wall_column;

		for (const auto& column : tile_map)
		{
			for (const auto& tile : column)
			{
				wall_column.push_back(tile.wall_box != nullptr);
			}
			wall_column.clear();
		}

	}

private:
	Map map;
};