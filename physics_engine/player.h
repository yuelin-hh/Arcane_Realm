#pragma once
#include "object.h"

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
				P = &Pr;
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
				P = &Pn;
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
		move();
	}

	void on_render(SDL_Renderer* renderer)
	{
		
	}

private:
	bool is_move_right = false;
	bool is_move_left = false;
	bool is_move_up = false;
	bool is_move_down = false;

	
	double Pn = 400;
	double Pr = 800;
	double* P = &Pn;
	double Fm =	1100;

	void move()
	{
		if (is_move_right - is_move_left != 0 || is_move_down - is_move_up != 0)
		{
			Vector2 direction(is_move_right - is_move_left, is_move_down - is_move_up);
			double speed = physics_box->get_velocity().get_speed_in_direction(direction);

			Vector2 direction_v(direction.y, -direction.x);
			double speed_v = physics_box->get_velocity().get_speed_in_direction(direction_v);

			double f = (physics_box->get_friction() <= 70 ? 70 : physics_box->get_friction());

			if (speed < (*P / f)* 6 / 7)
			{
				physics_box->add_impulse(Impulse(Velocity(direction, 1), m));
				physics_box->add_force(Force(direction, physics_box->get_friction()));
			}
			else
			{
				physics_box->add_force(Force(direction, *P / speed));
			}

			if (speed_v > 1)
			{
				direction_v.x = -direction_v.x;
				direction_v.y = -direction_v.y;

				physics_box->add_impulse(Impulse(Velocity(direction_v, 1), m));
			}
			else if (speed_v > 0 && speed_v <= 1)
			{
				direction_v.x = -direction_v.x;
				direction_v.y = -direction_v.y;

				physics_box->add_impulse(Impulse(Velocity(direction_v, speed_v), m));
			}
			else if (speed_v < -1)
			{
				physics_box->add_impulse(Impulse(Velocity(direction_v, 1), m));
			}
			else if (speed_v < 0 && speed_v >= -1)
			{
				physics_box->add_impulse(Impulse(Velocity(direction_v, -speed_v), m));
			}
		}
		else
		{
			double v1 = (physics_box->get_friction() <= 10 ? 10 : physics_box->get_friction()) / 100;

			if (physics_box->get_velocity().mgt() >= v1)
			{
				Vector2 direction = physics_box->get_velocity().direction();
				direction.x = -direction.x;
				direction.y = -direction.y;
				physics_box->add_impulse(Impulse(Velocity(direction, v1), m));
			}
			else
			{
				Vector2 direction = physics_box->get_velocity().direction();
				direction.x = -direction.x;
				direction.y = -direction.y;
				physics_box->add_impulse(Impulse(Velocity(direction, physics_box->get_velocity().mgt()), m));
			}
		}
	}
};