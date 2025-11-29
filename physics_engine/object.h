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

	const Vector2& get_position() { return position; }
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

	double max_speed = 7;
	double current_speed = max_speed;
	int counter = 10;

	void work_out_tile_pos()
	{
		tile_pos_x = position.x / 32;
		tile_pos_y = position.y / 32;
	}

	void find_way(int x, int y)
	{
		if (counter < 10)
		{
			counter++;
			return;
		}

		counter = 0;

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

	void move(Vector2 direction)
	{
		if (!direction.approx_zero())
		{
			double speed = physics_box->get_velocity().get_speed_in_direction(direction);

			Vector2 direction_v(direction.y, -direction.x);
			double speed_v = physics_box->get_velocity().get_speed_in_direction(direction_v);

			double f = (physics_box->get_friction() <= 50 ? 50 : physics_box->get_friction());

			if (speed <= 0)
			{
				physics_box->add_force(Force(direction, current_speed * 4 * f + f));
			}
			else
			{
				physics_box->add_force(Force(direction, current_speed * 4 * f + f - 4 * f * speed));
			}


			if (speed_v > 0.01)
			{
				physics_box->add_force(Force(direction_v, -f * 4));
			}
			else if (speed_v < -0.01)
			{
				physics_box->add_force(Force(direction_v, f * 4));
			}
			else if (speed_v > 0)
			{
				physics_box->add_impulse(Impulse(Velocity(direction_v, -speed_v), m));
			}
			else
			{
				physics_box->add_impulse(Impulse(Velocity(direction_v, speed_v), m));
			}
		}
		else
		{
			double v1 = (physics_box->get_friction() <= 10 ? 10 : physics_box->get_friction()) / 100;

			if (physics_box->get_velocity().mgt() >= v1)
			{
				Vector2 direction = physics_box->get_velocity().direction();
				direction.x = -direction.x;
				direction.y = -direction.y;
				physics_box->add_impulse(Impulse(Velocity(direction, v1), m));
			}
			else
			{
				Vector2 direction = physics_box->get_velocity().direction();
				direction.x = -direction.x;
				direction.y = -direction.y;
				physics_box->add_impulse(Impulse(Velocity(direction, physics_box->get_velocity().mgt()), m));
			}
		}
	}
};