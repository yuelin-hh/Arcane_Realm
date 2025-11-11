#pragma once
#include "manager.h"
#include "object.h"
#include "player.h"

class ObjectManager:public Manager<ObjectManager>
{
	friend class Manager<ObjectManager>;
public:
	using ObjectList = std::vector<std::shared_ptr<Object>>;

	void on_input(SDL_Event& event)
	{
		for(auto object:object_list)
			object->on_input(event);
	}

	void on_update(double delta)
	{
		if (flag)
		{
			object_list.push_back(std::make_shared<Player>());
			object_list[0]->set_position(100, 200);
			flag = false;
		}

		for (auto object : object_list)
		{
			object->on_update(delta);
		}
	}

	void on_render(SDL_Renderer* renderer)
	{
		for (auto object : object_list)
		{
			object->on_render(renderer);
		}
	}
protected:
	ObjectManager();
	~ObjectManager();

private:
	ObjectList object_list;

	bool flag = true;
};