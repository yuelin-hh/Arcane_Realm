#pragma once

#include "collision_layer.h"
#include "vector2.h"
#include "camera_manager.h"
#include "buff_manager.h"

#include <SDL.h>
#include <functional>

class CollideBox
{
public:
	CollideBox(CollisionShape shape, Vector2 size, const Vector2& position, int code);
	CollideBox(CollisionShape shape, double radius, const Vector2& position, int code);
	~CollideBox();

	void on_render(SDL_Renderer* renderer);

	void make_invalid()
	{
		is_valid = false;
	}

	void set_enable(bool flag)
	{
		enable = flag;
	}

	bool can_remove() const
	{
		return !is_valid;
	}

	bool is_enable()
	{
		return enable;
	}

	bool is_need_damage()
	{
		return need_damage;
	}

	void set_on_collide(std::function<void()> on_collide)
	{
		this->on_collide_attack = on_collide;
	}

	void set_on_collide(std::function<void(double, BuffManager::BuffList)> on_collide)
	{
		this->on_collide_struck = on_collide;
		need_damage = true;
	}

	void is_on_collide()
	{
		on_collide_attack();
	}

	void is_on_collide(double damage, BuffManager::BuffList list)
	{
		on_collide_struck(damage,list);
	}

	void set_layer_src(int src)
	{
		layer_src = src;
	}

	void set_layer_dst(int dst)
	{
		layer_dst = dst;
	}
	
	int get_layer_src()
	{
		return layer_src;
	}

	int get_layer_dst()
	{
		return layer_dst;
	}

	void set_damage(const double damage)
	{
		this->damage = damage;
	}

	double get_damage()
	{
		return damage;
	}

	void set_buff(BuffManager::BuffList &list)
	{
		buff_list = list;
	}

	const BuffManager::BuffList& get_buff()
	{
		return buff_list;
	}

	void set_self(bool flag)
	{
		is_self = flag;
	}

	bool get_is_self()
	{
		return is_self;
	}

	CollisionShape get_shape()
	{
		return shape;
	}

	const Vector2& get_position()
	{
		return position;
	}

	const Vector2& get_size()
	{
		return size;
	}

	const double& get_radius()
	{
		return radius;
	}

	void resize(double radius) 
	{
		this->radius = radius;
	}

	void resize(Vector2 size) 
	{
		this->size = size;
	}

	void set_lock(int target_code)
	{
		this->target_code = target_code;
	}

	const int get_lock_target()
	{
		return target_code;
	}

	const int get_code()
	{
		return code;
	}

protected:

private:
	std::function<void()> on_collide_attack;
	std::function<void(double, BuffManager::BuffList)> on_collide_struck;

	CollisionShape shape;
	const Vector2& position;
	Vector2 size;
	double radius = 0;
	double damage = 0;

	bool is_valid = true;
	bool enable = true;
	bool need_damage = false;
	bool is_self = false;

	int layer_src = 0;
	int layer_dst = 0;
	int code = 0;
	int target_code = 0;

	BuffManager::BuffList buff_list;
};