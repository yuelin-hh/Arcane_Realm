#include "physics_engine_manager.h"

PhysicsEngineManager::PhysicsEngineManager()
{
}

PhysicsEngineManager::~PhysicsEngineManager()
{
}

std::shared_ptr<PhysicsBox> PhysicsEngineManager::create_physics_box(Vector2 size, double m, Vector2& position)
{
	code++;
	std::shared_ptr<PhysicsBox> box = std::make_shared<PhysicsBox>(size, m, position, code);
	physics_box_list.push_back(box);
	return box;
}

std::shared_ptr<PhysicsBox> PhysicsEngineManager::create_physics_box(double radius, double m, Vector2& position)
{
	code++;
	std::shared_ptr<PhysicsBox> box = std::make_shared<PhysicsBox>(radius, m, position, code);
	physics_box_list.push_back(box);
	return box;
}

std::shared_ptr<WallBox> PhysicsEngineManager::create_wall_box(Vector2 pos, Vector2 size)
{
	std::shared_ptr<WallBox> box = std::make_shared<WallBox>(pos, size);
	wall_list.push_back(box);
	return box;
}

void PhysicsEngineManager::on_render(SDL_Renderer* renderer)
{
	for (auto box : physics_box_list)
	{
		box->on_render(renderer);
	}
	for (auto box : wall_list)
	{
		box->on_render(renderer);
	}
}