#pragma once

#include "object.h"

#include "buff_manager.h"
#include "enemy_type.h"
#include "bullet_manager.h"

#include <functional>

class Enemy :public Object
{
public:
	Enemy();
	virtual ~Enemy();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void cause_damage(double attack);

	void set_player_position(Vector2 pos)
	{
		player_position = pos;
	}

	void set_position(Vector2 pos)
	{
		position = pos;
	}

	void set_have_caused_damage()
	{
		have_caused_damage = false;
	}

	double get_damage()
	{
		return damage;
	}

	bool have_caused_damage = false;

protected:
	State state = Nullptr;

	Vector2 player_position;

	Animation anim_spawn;

	Animation anim_idle_left;
	Animation anim_idle_right;
	Animation anim_move_left;
	Animation anim_move_right;

	Animation anim_ready_left;
	Animation anim_ready_right;
	Animation anim_attack_left;
	Animation anim_attack_right;

	Animation anim_idle_left_sketch;
	Animation anim_idle_right_sketch;
	Animation anim_move_left_sketch;
	Animation anim_move_right_sketch;
	
	Animation anim_ready_left_sketch;
	Animation anim_ready_right_sketch;
	Animation anim_attack_left_sketch;
	Animation anim_attack_right_sketch;

	Animation* anim_current;
	Animation* anim_current_sketch;

	double hp = 100;
	double hp_max = 100;
	double speed = 1;
	double damage = 1;
	double attack_radius = 5;
	double view_radius = 200;
	double attack_interval = 2;

	double buff_damage = 0;

	bool is_show_sketch=false;
	bool is_on_spawn = true;
	bool can_attack = true;

	Timer timer_sketch;
	Timer timer_buff_damage;
	Timer timer_attack_interval;

	void buff_on_update(double delta);

	bool check_can_update(double delta);

	virtual void finish_attack();

	virtual void attack(double delta);

	virtual void is_dead();
private:
	bool is_find_target = false;

	void lock_target();

	void way_finding(double delta);

	void show_sketch();
};