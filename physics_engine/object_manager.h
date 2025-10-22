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
			auto object = std::make_shared<Object>();
			object->set_position(100, 400);
			object_list.push_back(object);

			object = std::make_shared<Object>();
			object->set_position(1100, 400);
			object_list.push_back(object);

			object = std::make_shared<Object>();
			object->set_position(800, 440);
			object_list.push_back(object);

			object = std::make_shared<Object>();
			object->set_position(600, 440);
			object_list.push_back(object);

			object = std::make_shared<Object>();
			object->set_position(600, 640);
			object_list.push_back(object);

			flag = false;
		}
		for (auto object : object_list)
		{
			object->on_update(delta);
		}
	}

	void on_render(SDL_Renderer* renderer)
	{
	}
protected:
	ObjectManager();
	~ObjectManager();

private:
	ObjectList object_list;

	bool flag = true;
};