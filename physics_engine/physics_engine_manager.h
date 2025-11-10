#pragma once
#include "manager.h"
#include "physics_collide_box.h"
#include "wall_box.h"
#include "tile.h"
#include <array>

struct BoxAndTime
{
	std::shared_ptr<PhysicsBox> box = nullptr;
	double t = 0;
};

class PhysicsEngineManager:public Manager<PhysicsEngineManager>
{
	friend class Manager<PhysicsEngineManager>;
public:
	using PhysicsBoxList = std::vector<std::shared_ptr<BoxAndTime>>;
	using WallBoxList = std::vector<std::shared_ptr<WallBox>>;
	using ResultList = std::vector < std::array<std::shared_ptr<BoxAndTime>,2>>;

	std::shared_ptr<PhysicsBox> create_physics_box(Vector2 size, double m, Vector2& position);
	std::shared_ptr<PhysicsBox> create_physics_box(double radius, double m, Vector2& position);
	std::shared_ptr<WallBox> create_wall_box(Vector2 pos, Vector2 size);

	void on_update(double delta)
	{
		//if (flag)
		//{
		//	physics_box_list[0]->box->set_u(0.2);
		//	physics_box_list[0]->box->set_cannot_bounce();
		//	physics_box_list[1]->box->set_u(0.2);
		//	physics_box_list[1]->box->set_cannot_bounce();
		//	/*for (auto box : physics_box_list)
		//	{
		//		box->box->set_u(0);
		//		box->box->set_can_bounce();
		//	}
		//	physics_box_list[5]->box->set_u(0.2);
		//	physics_box_list[5]->box->set_cannot_bounce();

		//	physics_box_list[0]->box->add_impulse(Impulse(Velocity(10,0),50));
		//	physics_box_list[1]->box->add_impulse(Impulse(Velocity(-13,0),50));
		//	physics_box_list[2]->box->add_impulse(Impulse(Velocity(-5,9),50));
		//	physics_box_list[3]->box->add_impulse(Impulse(Velocity(-5,9),50));
		//	physics_box_list[4]->box->add_impulse(Impulse(Velocity(-9,9),50));*/
		//	flag = false;
		//}

		for (auto box : physics_box_list)
		{
			box->box->on_update(delta);
		}

		check_collide_possible(delta);
		check_collide(delta);

		for (auto box : physics_box_list)
		{
			check_collide_with_wall(box, box->t);
		}
	}
	
	void on_render(SDL_Renderer* renderer);

	

	void set_map(TileMap& tile_map)
	{
		this->tile_map = tile_map;
	}

protected:
	PhysicsEngineManager();
	~PhysicsEngineManager();

private:
	

	int code = 0;

	bool flag = true;

	TileMap tile_map;
	PhysicsBoxList physics_box_list;
	WallBoxList wall_list;
	ResultList result_list;

	void check_collide_with_wall(std::shared_ptr<BoxAndTime> box, double t);

	void check_collide_possible(double t);

	void check_collide(double t);

	void make_collision(std::shared_ptr<BoxAndTime> box1, std::shared_ptr<BoxAndTime> box2, double t);

	void add_impulse(std::shared_ptr<PhysicsBox> box1, std::shared_ptr<PhysicsBox> box2, bool is_left_and_right);

	int get_symbol(double a)
	{
		if (a == 0)
		{
			return 0;
		}
		else if (a < 0)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	void print()
	{
		for (const auto& a : tile_map)
		{
			for (const auto& b : a)
			{
				std::cout << b.wall << " ";
			}
			std::cout << "\n";
		}
	}
};

