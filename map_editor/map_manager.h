#pragma once
#include "manager.h"
#include "map.h"

class MapManager: public Manager<MapManager>
{
	friend class Manager<MapManager>;
protected:
	MapManager();
	~MapManager();
public:

private:

};

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}