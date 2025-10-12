#pragma once

#include "object.h"

#include "ui_manager.h"
#include "bullet_manager.h"
#include "magic_manager.h"
#include "buff_manager.h"

#include <SDL2_gfxPrimitives.h>

class Player :public Object
{
public:
	Player();
	~Player();

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_renderer(SDL_Renderer* renderer);

	void get_camera_position(Vector2 pos)
	{
		camera_position = pos;
	}

	double get_max_hp()
	{
		return hp_max;
	}

	double get_hp()
	{
		return hp;
	}

	double get_max_mp()
	{
		return mp_max;
	}

	double get_mp()
	{
		return mp;
	}

	bool is_dead = false;
protected:

	double angle_anim_rotated;

	std::shared_ptr<Vector2> mouse_position;
	Vector2 camera_position ;
	Vector2 shoot_position;

	bool is_move_right = false;
	bool is_move_left = false;
	bool is_move_up = false;
	bool is_move_down = false;

	bool is_facing_right = true;

	Animation anim_lock_ui;

	Animation anim_idle_right;
	Animation anim_run_right;
	Animation anim_idle_left;
	Animation anim_run_left;

	Animation anim_wand_idle;
	Animation anim_wand_attack;

	Animation* anim_current = nullptr;
	Animation* anim_wand = nullptr;

	Timer timer_attack_cd;
	Timer timer_show_radius;
	Timer timer_show_sketch;

	Magic* current_magic = nullptr;
	Magic* last_magic = nullptr;

	double hp_max = 500;
	double hp = 0;
	double speed = 3;
	double attack = 1;
	double attack_multiplier = 10;
	double attack_interval = 0.5;
	double attack_radius = 320;
	double bullet_speed = 300;
	double mp_max = 10;
	double mp = 0;
	double mp_recover = 0.5;

	double change_speed = 1;

	bool can_attack = true;
	bool is_show_attack_radius = false;
	bool is_show_sketch = false;

	std::shared_ptr<Object> find_target_enemy(double radious);

	void wand_attack();

	void release_magic();

	void set_magic_parameter();

	void workout_randian();

	Vector2 workout_shoot_velocity();

	void workout_shoot_position();

	void set_ui();

	void try_attack();

	void magic_take_effect();

	void cause_damage(double damage);
};