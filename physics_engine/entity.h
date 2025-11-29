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
		current_speed = max_speed;

		find_way(player_position.x / 32, player_position.y / 32);

		Vector2 direction;

		direction.x = smoothed_ways[0][0] * 32 + 16 - position.x;
		direction.y = smoothed_ways[0][1] * 32 + 16 - position.y;

		if (direction.length()<16 && smoothed_ways.size() > 1)
		{
			direction.x = smoothed_ways[1][0] * 32 + 16 - position.x;
			direction.y = smoothed_ways[1][1] * 32 + 16 - position.y;
		}

		move(direction);
	}

	void on_render(SDL_Renderer* renderer)
	{
		if (smoothed_ways.empty()) return;
		SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);

		SDL_RenderDrawLine(renderer, position.x, position.y,
			smoothed_ways[0][0] * 32 + 16, smoothed_ways[0][1] * 32 + 16);
		for (int i = 0; i < smoothed_ways.size() - 1; i++)
		{
			SDL_RenderDrawLine(renderer, smoothed_ways[i][0] * 32 + 16, smoothed_ways[i][1] * 32 + 16,
				smoothed_ways[i + 1][0] * 32 + 16, smoothed_ways[i + 1][1] * 32 + 16);
		}
	}

private:
	Vector2 player_position;
};