#pragma once
#include "physics_engine_manager.h"
#include "memory.h"
#include "way_finding_manager.h"
#include "check_manager.h"

class Object
{
public:
	Object();
	~Object();

	void set_position(Vector2 pos)
	{
		position = pos;
	}
	void set_position(double x, double y)
	{
		position.x = x;
		position.y = y;
	}

	virtual void on_input(SDL_Event& event){}
	virtual void on_update(double delta){}
	virtual void on_render(SDL_Renderer* renderer){}

protected:
	std::shared_ptr<PhysicsBox> physics_box;
	Result ways;
	Result smoothed_ways;

	Vector2 position;
	Vector2 size;
	double radius;
	double m = 50;
	int tile_pos_x = 0;
	int tile_pos_y = 0;

	void work_out_tile_pos()
	{
		tile_pos_x = position.x / 32;
		tile_pos_y = position.y / 32;
	}

	void find_way(int x, int y)
	{
		work_out_tile_pos();

		if (!WayFindingManager::instance()->find_way_to(tile_pos_x, tile_pos_y, x, y).empty())
			ways = WayFindingManager::instance()->find_way_to(tile_pos_x, tile_pos_y, x, y);

		smooth_ways();
	}

	void smooth_ways()
	{
		for (int i = ways.size() - 1; i >= 0; i--)
		{
			Vector2 distance(ways[i][0] * 32 + 16 - position.x, ways[i][1] * 32 + 16 - position.y);
			if (CheckManager::instance()->check_no_wall_in_rect(position, size, distance))
			{
				smoothed_ways.clear();
				for (int j = i; j < ways.size(); j++)
				{
					smoothed_ways.push_back(ways[j]);
				}
				return;
			}
		}
		smoothed_ways = ways;
	}
};