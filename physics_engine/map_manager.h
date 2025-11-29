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
	}

private:
	Map map;
};