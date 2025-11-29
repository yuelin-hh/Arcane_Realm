#pragma once
#include "button.h"
#include <memory>

using ButtonList = std::vector<std::shared_ptr<Button>>;

class ButtonGroup
{
public:
	ButtonGroup();
	~ButtonGroup();

	void on_input(const SDL_Event& event)
	{
		for (auto each : button_list)
		{
			each->on_input(event);
		}
	}

	void on_update(double delta)
	{
	}

	void on_render(SDL_Renderer* renderer)
	{
		for (auto each : button_list)
		{
			each->on_render(renderer);
		}
	}
protected:
	ButtonList button_list;
};

ButtonGroup::ButtonGroup()
{
}

ButtonGroup::~ButtonGroup()
{
}