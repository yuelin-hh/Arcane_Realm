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

private:
	Map map;
};

MapManager::MapManager()
{
	map.load("map.csv");
}

MapManager::~MapManager()
{
}