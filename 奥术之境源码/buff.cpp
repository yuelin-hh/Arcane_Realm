#include "buff.h"

Buff::Buff()
{
}

Buff::~Buff()
{
}

void Buff::on_update(double delta)
{
	timer.on_update(delta);
	anim_effect.on_update(delta);
}

void Buff::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;
	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);

	anim_effect.on_render(renderer, point);
}