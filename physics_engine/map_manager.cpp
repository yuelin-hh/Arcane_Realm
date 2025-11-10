#include "map_manager.h"

MapManager::MapManager()
{
	map.load("map1.csv");
	create_wall_map();
	PhysicsEngineManager::instance()->set_map(map.get_tile_map());
}

MapManager::~MapManager()
{
}