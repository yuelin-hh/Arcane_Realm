#pragma once
#include "manager.h"
#include "group_file.h"
#include "group_select.h"
#include "group_tile.h"

class ButtonManager: public Manager<ButtonManager>
{
	friend class Manager<ButtonManager>;
protected:
	ButtonManager();
	~ButtonManager();
public:
	void on_input(const SDL_Event& event)
	{
		group_sellect.on_input(event);
		if (current_group)
			current_group->on_input(event);
	}

	void on_update(double delta)
	{
		read_message_select();
		group_sellect.on_update(delta);
		if (current_group)
			current_group->on_update(delta);
	}

	void on_render(SDL_Renderer* renderer)
	{
		group_sellect.on_render(renderer);
		if (current_group)
			current_group->on_render(renderer);
	}
private:
	GroupSelect group_sellect;
	ButtonGroup* current_group = nullptr;
	GroupFile group_file;
	GroupTile group_tile;
	std::string topic_select = "select";

	void read_message_select()
	{
		std::string value = MessageManager::instance()->read_message(topic_select);
		if (!value.empty())
		{
			int mode = Transcoder::read_int_message(value);
			if (mode == 0) current_group = &group_file;
			else if (mode == 1) current_group = &group_tile;
		}
	}
};

ButtonManager::ButtonManager()
{
	current_group = &group_file;
}

ButtonManager::~ButtonManager()
{
}