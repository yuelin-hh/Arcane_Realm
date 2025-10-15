#pragma once
#include "manager.h"
#include "physics_collide_box.h"

class PhysicsEngineManager:public Manager<PhysicsEngineManager>
{
	friend class Manager<PhysicsEngineManager>;
public:
	using PhysicsBoxList = std::vector<std::shared_ptr<PhysicsBox>>;

	std::shared_ptr<PhysicsBox> create_physics_box(Vector2 size, double m, Vector2& position);
	std::shared_ptr<PhysicsBox> create_physics_box(double radius, double m, Vector2& position);

	void on_update(double delta)
	{
		if (flag)
		{
			physics_box_list[0]->add_impulse(Impulse(Velocity(7, 0), 50));
			physics_box_list[0]->set_u(0.2);
			physics_box_list[1]->set_u(0.2);
			flag = false;
		}

		physics_box_list[0]->add_force(Force(100, 0));

		for (auto box : physics_box_list)
		{
			box->on_update(delta);
		}
	}

	void on_render(SDL_Renderer* renderer);

protected:
	PhysicsEngineManager();
	~PhysicsEngineManager();

private:
	int code = 0;

	bool flag = true;

	PhysicsBoxList physics_box_list;
};

