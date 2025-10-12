#pragma once

#include "object.h"

#include "bullet_type.h"
#include "buff_manager.h"

class Bullet :public Object
{
public:
	Bullet();
	~Bullet();

	virtual void on_update(double delta);

	virtual void on_render(SDL_Renderer* renderer);

	void set_bullet_parameter(double damage, double speed, std::shared_ptr<Object> target, Vector2 pos, BuffManager::BuffList list);

	void set_bullet_parameter(double damage, double distance, double speed, Vector2 shoot_velocity, Vector2 start_pos, Vector2 pos, BuffManager::BuffList list);

	void set_bullet_parameter(double damage, std::shared_ptr<Object> target, BuffManager::BuffList list);

	void set_bullet_parameter(double damage, double distance, Vector2 pos, BuffManager::BuffList list, double duration = 0);

protected:
	double speed = 0;
	double damage = 0;
	double distance = 0;
	double duration = 0;

	bool is_collide = false;

	Vector2 start_pos;
	Vector2 target_position;
	Vector2 target_size;

	Animation anim_bullet_fly;
	Animation anim_bullet_attack;
	Animation* anim_current;

	BulletType type;

	std::shared_ptr<Object> target = nullptr;

private:

protected:
	void deliver_buff(std::shared_ptr<Object> enemy);
};