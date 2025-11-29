#pragma once
#include "vector2.h"
#include "animation.h"

#include <SDL.h>
#include <functional>

class Button
{
public:
	Button();
	~Button();

	void set_on_click(std::function<void()> on_click)
	{
		this->on_click = on_click;
	}

	void on_input(const SDL_Event& event)
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) 
			{
			case SDL_BUTTON_LEFT:
				if (event.motion.x >= rect.x && event.motion.x <= rect.x + rect.w
					&& event.motion.y >= rect.y && event.motion.y <= rect.y + rect.h)
					on_click();
				break;
			}
		default:
			break;
		}
	}

	void set_anim(SDL_Texture* texture, int num_h, int num_v, const std::vector<int>& idx_list)
	{
		anim.set_frame_data(texture, num_h, num_v, idx_list);
	}

	void set_rect(const SDL_Rect& rect)
	{
		this->rect = rect;
	}

	void on_render(SDL_Renderer* renderer)
	{
		anim.on_render(renderer, rect);
	}

private:
	SDL_Rect rect;
	std::function<void()> on_click;
	Animation anim;
};

Button::Button()
{
}

Button::~Button()
{
}