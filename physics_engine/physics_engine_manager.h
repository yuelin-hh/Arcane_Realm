#pragma once
#include "manager.h"
#include "physics_collide_box.h"
#include "wall_box.h"
#include "tile.h"

class PhysicsEngineManager:public Manager<PhysicsEngineManager>
{
	friend class Manager<PhysicsEngineManager>;
public:
	using PhysicsBoxList = std::vector<std::shared_ptr<PhysicsBox>>;
	using WallBoxList = std::vector<std::shared_ptr<WallBox>>;

	std::shared_ptr<PhysicsBox> create_physics_box(Vector2 size, double m, Vector2& position);
	std::shared_ptr<PhysicsBox> create_physics_box(double radius, double m, Vector2& position);
	std::shared_ptr<WallBox> create_wall_box(Vector2 pos, Vector2 size);

	void on_update(double delta)
	{
		if (flag)
		{
			physics_box_list[0]->set_u(0);
			physics_box_list[1]->set_u(0.2);
			physics_box_list[0]->add_impulse(Impulse(Velocity(10,4),50));
			physics_box_list[0]->set_can_bounce();
			flag = false;
		}

		for (auto box : physics_box_list)
		{
			box->on_update(delta);
		}

		check_collide_with_wall(delta);
	}
	
	void on_render(SDL_Renderer* renderer);

	void check_collide_with_wall(double t);

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

