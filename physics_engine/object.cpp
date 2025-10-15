#include "object.h"

Object::Object()
{
	size.x = 32;
	size.y = 32;

	physics_box = PhysicsEngineManager::instance()->create_physics_box(size, m, position);
}

Object::~Object()
{
}