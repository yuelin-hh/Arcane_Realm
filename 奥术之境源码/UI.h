#pragma once

#include "object.h"

class UI
{
public:
	UI();
	~UI();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_lock_target(std::shared_ptr<Object> enemy);

	void on_attack_lock();

	void set_mouse_position(Vector2 pos)
	{
		mouse_position = pos;
	}

	void set_lock_ui_follow(bool flag)
	{
		is_lock_ui_fllow = flag;
	}

	void set_show_lock_ui(bool flag)
	{
		is_show_lock_ui = flag;
	}

	void set_follow_ui_valid(bool flag);

private:
	bool is_lock_ui_on_target=false;
	bool is_lock_ui_fllow = false;
	bool is_show_lock_ui = true;

	Vector2 position_target;
	Vector2 size_target;
	Vector2 mouse_position;

	Animation anim_ui_lock;
	Animation anim_ui_lock_attack;

	Animation* anim_ui_lock_current;
};