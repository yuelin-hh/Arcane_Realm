#pragma once
#include "manager.h"
#include "object.h"
#include "player.h"

class ObjectManager:public Manager<ObjectManager>
{
	friend class Manager<ObjectManager>;
public:
	using ObjectList = std::vector<std::shared_ptr<Object>>;

	void on_update(double delta)
	{
		if (flag)
		{
			auto object = std::make_shared<Object>();
			object->set_position(0, 240);
			object_list.push_back(object);
			
			object = std::make_shared<Player>();
			object->set_position(0, 480);
			object_list.push_back(object);

			flag = false;
		}
		object_list[1]->on_update(delta);

	}

	void on_render(SDL_Renderer* renderer)
	{
		object_list[1]->on_render(renderer);
	}
protected:
	ObjectManager();
	~ObjectManager();

private:
	ObjectList object_list;

	bool flag = true;
};