#pragma once
#include"buff_type.h"
#include"vector2.h"
#include"animation.h"
#include "config_manager.h"
#include "resources_manager.h"

class Buff
{
public:
	Buff();
	~Buff();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_position(Vector2 pos)
	{
		position = pos;
	}

	void make_invalid()
	{
		is_valid = false;
	}

	bool can_remove()const
	{
		return !is_valid;
	}

	void reset()
	{
		timer.restart();
	}

	double cause_damage()
	{
		return damage;
	}

	double cause_recover()
	{
		return recover;
	}

	double cause_speed_up()
	{
		return speed_up;
	}

	BuffName name;
protected:
	double duration = 5;
	double damage = 0;
	double recover = 0;
	double speed_up = 0;

	bool is_valid = true;

	Vector2 size;
	Vector2 position;

	Animation anim_effect;

	Timer timer;
};