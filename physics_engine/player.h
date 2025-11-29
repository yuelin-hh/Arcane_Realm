#pragma once
#include "object.h"
#include <cmath>

class Player:public Object
{
public:
	Player();
	~Player();

	void on_input(SDL_Event& event) override
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				is_move_left = true;
				break;
			case SDLK_d:
				is_move_right = true;
				break;
			case SDLK_w:
				is_move_up = true;
				break;
			case SDLK_s:
				is_move_down = true;
				break;
			case SDLK_LSHIFT:
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				is_move_left = false;
				break;
			case SDLK_d:
				is_move_right = false;
				break;
			case SDLK_w:
				is_move_up = false;
				break;
			case SDLK_s:
				is_move_down = false;
				break;
			case SDLK_LSHIFT:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	void on_update(double delta)
	{
		current_speed = max_speed;
		move(Vector2(is_move_right - is_move_left, is_move_down - is_move_up));
		
	}

	void on_render(SDL_Renderer* renderer)
	{
		//std::cout << physics_box->get_velocity().x << "   " << physics_box->get_velocity().y << std::endl;
	}

private:
	bool is_move_right = false;
	bool is_move_left = false;
	bool is_move_up = false;
	bool is_move_down = false;
};