#pragma once

#include "manager.h"
#include "collide_box.h"
#include "vector2.h"

#include <vector>
#include <memory>
#include <SDL.h>

class CollisionManager : public Manager<CollisionManager>
{
	friend class Manager<CollisionManager>;
public:
	using CollideBoxList = std::vector<std::shared_ptr<CollideBox>>;

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	std::shared_ptr<CollideBox> create_collide_box(Vector2 size, const Vector2& position);

	std::shared_ptr<CollideBox> create_collide_box(double radius, const Vector2& position);

	std::shared_ptr<CollideBox> create_mouse_box(double radius, const Vector2& position);

	bool check_mouse_collide(std::shared_ptr<CollideBox> box);

	const CollideBoxList& get_collide_box_list()
	{
		return collide_box_list;
	}

private:
	CollisionManager();
	~CollisionManager();

	int code = 1;

	std::shared_ptr<CollideBox> mouse_box;
	CollideBoxList collide_box_list;

	void remove_invalid_box();

	void check_collide();
};