#pragma once

#include "animation.h"

class Retention
{
public:
	Retention();
	~Retention();

	void on_render(SDL_Renderer* renderer, SDL_Point point, double angle);

	void set_animation(Animation* anim);

private:
	Animation *anim;

};