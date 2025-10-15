#pragma once
#include "vector2.h"

#include <SDL.h>
#include <iostream>
struct WallBox
{
	WallBox(Vector2 positon,Vector2 size);
	~WallBox();

	void on_render(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		rect.x = int(position.x);
		rect.y = int(position.y);
		rect.w = int(size.x);
		rect.h = int(size.y);

		SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
		SDL_RenderDrawRect(renderer, &rect);
	}

	Vector2 position;
	Vector2 size;
};