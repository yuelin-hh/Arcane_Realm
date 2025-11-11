#pragma once
#include "physics_engine_manager.h"
#include "memory.h"
#include "way_finding_manager.h"

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
		if (!WayFindingManager::instance()->find_way_to(tile_pos_x, tile_pos_y, x, y).empty())
			ways = WayFindingManager::instance()->find_way_to(tile_pos_x, tile_pos_y, x, y);
	}
};