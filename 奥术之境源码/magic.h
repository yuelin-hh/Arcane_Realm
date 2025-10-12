#pragma once

#include "vector2.h"
#include "animation.h"
#include "timer.h"
#include "bullet_manager.h"
#include "buff_manager.h"

#include<SDL_ttf.h>

/*
写了新magic在select的load_config里和magicmanager的on_enter里加上
*/

class Magic
{
public:
	Magic();
	~Magic();

	void on_update(double delta)
	{
		anim_magic_current->on_update(delta);
	}

	void on_render(SDL_Renderer* renderer)
	{
		SDL_Point point;
		point.x = (int)(position_angle.x);
		point.y = (int)(position_angle.y);
		anim_magic_current->on_render_lock(renderer, point);

		small_number_on_render(renderer);

	}

	void set_position(double x, double y)
	{
		position_angle.x = x;
		position_angle.y = y;
	}

	void on_render_chose(SDL_Renderer* renderer)
	{
		SDL_Point point;
		point.x = (int)(position_angle.x-40);
		point.y = (int)(position_angle.y-160);
		anim_magic_current->set_scaling(1);
		anim_magic_current->on_render_lock(renderer, point);
		if (!is_on_cd && is_mp_sufficien)
			anim_ui_can_release.on_render_lock(renderer, point);
		else
			anim_ui_cannot_release.on_render_lock(renderer, point);
		anim_magic_current->set_scaling(0.5);
		big_number_on_recder(renderer);
	}

	bool check_can_fire()
	{
		if (!is_on_cd && is_mp_sufficien)
		{
			if (need_target)
			{
				if (target != nullptr)
					return true;
				else
					return false;
			}
			else if (need_mouse_position)
			{
				if ((mouse_position - player_position).length() >= radius)
				{
					mouse_position = player_position + (mouse_position - player_position).normalize() * radius;
				}
				else
					return true;
			}
				return true;
		}
		return false;
	}

	virtual void release(double attack)
	{
		anim_magic_current = &anim_magic_cd;
		is_on_cd = true;
		anim_magic_current->reset();
		anim_magic_current->set_on_finished([&]() {
			is_on_cd = false;
			anim_magic_current = &anim_magic;
			});
	}

	void set_velocity(Vector2 velocity)
	{
		this->velocity = velocity;
	}

	void set_start_position(Vector2 pos)
	{
		start_position = pos;
	}

	void set_target_enemy(std::shared_ptr<Object> enemy)
	{
		target = enemy;
	}

	void set_player_position(Vector2 pos)
	{
		player_position = pos;
	}

	void set_mouse_position(Vector2 pos)
	{
		mouse_position = pos;
	}

	void check_mp_sufficien(double mp)
	{
		if (mp >= consumption)
			is_mp_sufficien = true;
		else
			is_mp_sufficien = false;
	}

	double get_consumption()
	{
		return consumption;
	}

	double get_radious()
	{
		return radius;
	}

	double get_range()
	{
		return range;
	}

	BuffManager& get_buff_manager()
	{
		return buff_manager;
	}

	bool need_velocity = false;
	bool need_player_position = false;
	bool need_start_position = false;
	bool need_target = false;
	bool need_mouse_position = false;
	bool is_self = false;

protected:
	double consumption = 2;
	double cd = 1;
	double multiplier = 20;
	double radius = 500;
	double speed = 400;
	double range = 0;

	bool is_on_cd = false;
	bool is_mp_sufficien = true;

	Vector2 size;
	Vector2 position_angle;
	Vector2 velocity;
	Vector2 player_position;
	Vector2 start_position;
	Vector2 mouse_position;

	Animation anim_magic;
	Animation anim_magic_cd;
	Animation anim_ui_can_release;
	Animation anim_ui_cannot_release;

	Animation* anim_magic_current;

	std::shared_ptr<Object> target = nullptr;

	BuffManager buff_manager;

	SDL_Color color_red = { 255,0,0,255 };
	SDL_Color color_black = { 0,0,0,255 };
	TTF_Font* font;

	void small_number_on_render(SDL_Renderer* renderer);

	void big_number_on_recder(SDL_Renderer* renderer);
};