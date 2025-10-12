#pragma once

#include "vector2.h"
#include "animation.h"
#include "resources_manager.h"
#include "config_manager.h"
#include "collision_manager.h"
#include "tools.h"

#include <SDL.h>

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void on_input(const SDL_Event& event);

	virtual void on_update(double delta);

	virtual void on_renderer(SDL_Renderer* renderer);

	const Vector2& get_position() const
	{
		return position;
	}

	const Vector2& get_size() const
	{
		return size;
	}

	void deliver_buff(const BuffManager::BuffList &list)
	{
		buff_manager.deliver_buff(list);
	}

	const std::shared_ptr<CollideBox> get_collide_box()
	{
		return collide_box;
	}

	bool can_remove() const
	{
		return !is_valid;
	}

protected:
	bool is_valid = true;

	Vector2 size;
	Vector2 position;
	Vector2 velocity;
	std::shared_ptr<CollideBox> collide_box;

	BuffManager buff_manager;

	void make_invalid()
	{
		is_valid = false;
	}
};