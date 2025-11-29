#pragma once
#include "manager.h"
#include "string"

struct InputField
{
	SDL_Rect input_rect;
	std::string text;
	bool isActive;
	SDL_Color bgColor;
	SDL_Color textColor;
};

class InputManager: public Manager<InputManager>
{
	friend class Manager<InputManager>;
protected:
	InputManager();
	~InputManager();

	void input(int& size_x, int& size_y)
	{
		window = SDL_CreateWindow("Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			640, 320, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		SDL_RenderSetLogicalSize(renderer, 640, 360);

		InputField field1 = if1;
		InputField field2 = if2;

		while (true)
		{
			while(SDL_PollEvent(&event))
			{
				switch (event)
				{
				default:
					break;
				}
			}
		}






		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
private:
	SDL_Event event;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	InputField if1 = {
		{100, 100, 200, 30},
		"",
		false,
		{150, 150, 150, 150},
		{255, 255, 255, 255}
	};
	InputField if2 = {
		{100, 150, 200, 30},
		"",
		false,
		{150, 150, 150, 150},
		{255, 255, 255, 255}
	};
};

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}