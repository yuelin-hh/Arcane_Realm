#pragma once
#include "bullet.h"

class FireballBullet: public Bullet
{
public:
	FireballBullet();
	~FireballBullet();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	std::shared_ptr<CollideBox> damage_box;
	void find_ways(double delta);
};