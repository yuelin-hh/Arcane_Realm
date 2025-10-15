#pragma once
#include "physics_engine_manager.h"
#include "memory.h"


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

	Vector2 position;
	Vector2 size;
	double radius;
	double m = 50;
};