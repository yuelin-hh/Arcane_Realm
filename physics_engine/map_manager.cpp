#include "map_manager.h"
#include "way_finding_manager.h"
#include "check_manager.h"
#include "physics_engine_manager.h"
#include "create_wall_tool.h"

MapManager::MapManager()
{
	map.load("map1.csv");
	create_wall_map();
	PhysicsEngineManager::instance()->set_map(&map);
	WayFindingManager::instance()->set_map(&map);
	CheckManager::instance()->set_map(&map);
	CreateWallTool::instance()->set_map(&map);
}

MapManager::~MapManager()
{
}