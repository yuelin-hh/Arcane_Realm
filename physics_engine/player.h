#pragma once
#include "object.h"

class Player:public Object
{
public:
	Player();
	~Player();

	void on_input(SDL_Event& event)
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
		t += delta * 100;
		if (is_move_right - is_move_left != 0 || is_move_down - is_move_up != 0)
		{
			//Vector2 direction(is_move_right - is_move_left, is_move_down - is_move_up);
			Vector2 direction(1, 0);

			double speed = physics_box->get_velocity().get_speed_in_direction(direction);
			speed1 = speed * 100;
			if (speed < 6)
			{
				physics_box->add_impulse(Impulse(Velocity(direction, 1), m));
				
				//physics_box->add_force(Force(direction, Fm));
			}
			else
			{
				flag = false;
				physics_box->add_force(Force(direction, P / speed));
			}

			
		}
		
	}

	void on_render(SDL_Renderer* renderer)
	{
		/*SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
		SDL_RenderDrawLine(renderer, 0, 20, 1280, 20);
		if(flag)
			SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
		else
			SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
		SDL_RenderDrawPoint(renderer, t, 720 - speed1);*/
	}
private:
	bool is_move_right = true;
	bool is_move_left = false;
	bool is_move_up = false;
	bool is_move_down = false;

	double P = 700;
	double Fm =	1100;

	double speed1 = 0;
	double t = 0;

	bool flag = true;
};