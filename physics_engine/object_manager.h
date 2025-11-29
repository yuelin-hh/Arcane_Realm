#pragma once
#include "manager.h"
#include "object.h"
#include "player.h"
#include "entity.h"

class ObjectManager:public Manager<ObjectManager>
{
	friend class Manager<ObjectManager>;
public:
	using EntityList = std::vector<std::shared_ptr<Entity>>;

	void on_input(SDL_Event& event)
	{
		if(player)
			player->on_input(event);
	}

	void on_update(double delta)
	{
		if (flag)
		{
			player = std::make_shared<Player>();
			entity_list.push_back(std::make_shared<Entity>());
			entity_list[0]->set_position(100, 200);
			player->set_position(500, 200);
			flag = false;
		}

		player->on_update(delta);

		for (auto entity : entity_list)
		{
			entity->set_player_position(player->get_position());
			entity->on_update(delta);
		}
	}

	void on_render(SDL_Renderer* renderer)
	{
		player->on_render(renderer);

		for (auto entity : entity_list)
		{
			entity->on_render(renderer);
		}
	}
protected:
	ObjectManager();
	~ObjectManager();

private:
	EntityList entity_list;
	std::shared_ptr<Player> player;

	bool flag = true;
};