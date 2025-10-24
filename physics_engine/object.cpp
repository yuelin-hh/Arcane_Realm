#include "object.h"

Object::Object()
{
	size.x = 28;
	size.y = 28;

	physics_box = PhysicsEngineManager::instance()->create_physics_box(size, m, position);
}

Object::~Object()
{
}