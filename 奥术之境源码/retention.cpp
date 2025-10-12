#include "retention.h"

Retention::Retention()
{
}

Retention::~Retention()
{
}

void Retention::set_animation(Animation* anim)
{
	this->anim = anim;
}

void Retention::on_render(SDL_Renderer* renderer, SDL_Point point, double angle)
{
	anim->on_render(renderer, point, angle);
}