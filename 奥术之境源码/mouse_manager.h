#pragma once
#include "manager.h"
#include "vector2.h"
#include "collision_manager.h"
#include "object.h";
#include "camera_manager.h"

#include <SDL.h>

using ObjectList = std::vector<std::shared_ptr<Object>>;

class MouseManager: public Manager<MouseManager>
{
	friend class Manager< MouseManager>;
public:
	void on_input(const SDL_Event& event);

	void set_enemylist(const ObjectList& list)
	{
		enemy_list = list;
	}

	const std::shared_ptr<Object> get_target_enemy(Vector2 player_pos, double radious);

	const std::shared_ptr<Vector2> get_mouse_position()
	{
		std::shared_ptr<Vector2> point(&position);
		return point;
	}

	void set_left_button_on_click(std::function<void()> function) { left_button_on_click = function; }

	void set_right_button_on_click(std::function<void()> function) { right_button_on_click = function; }

	void set_middle_button_on_click(std::function<void()> function) { middle_button_on_click = function; }

	const ObjectList& get_enemy_list()
	{
		return enemy_list;
	}

protected:
	MouseManager();
	~MouseManager();

private:
	Vector2 position;
	Vector2 relative_position;
	std::shared_ptr<Vector2> camera_position;
	Vector2 target_position;
	ObjectList enemy_list;

	std::function<void()> left_button_on_click;
	std::function<void()> right_button_on_click;
	std::function<void()> middle_button_on_click;

	std::shared_ptr<CollideBox> mouse_box;
};