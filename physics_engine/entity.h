#pragma once
#include "object.h"

class Entity : public Object
{
public:
	Entity();
	~Entity();

	void set_player_position(Vector2 player_position)
	{
		this->player_position = player_position;
	}

	void on_update(double delta)
	{

	}

	void on_renderer(SDL_Renderer* renderer)
	{

	}

private:
	Vector2 player_position;

	void move(double t)
	{
		Vector2 direction(smoothed_ways[0][0] - position.x, smoothed_ways[0][1] - position.y);

	}
};