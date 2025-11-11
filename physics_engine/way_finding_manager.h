#pragma once
#include "manager.h"
#include "wayfinding.h"

class WayFindingManager : public Manager<WayFindingManager>
{
	friend class Manager<WayFindingManager>;
protected:
	WayFindingManager();
	~WayFindingManager();

public:
	void set_map(Map* map)
	{
		way_finding.set_map(map);
	}

	Result find_way_to(int x1, int y1, int x2, int y2)
	{
		return way_finding.find_way(x1, y1, x2, y2);
	}

private:
	WayFinding way_finding;
};