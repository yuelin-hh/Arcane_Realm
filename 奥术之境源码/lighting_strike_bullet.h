#pragma once
#include "bullet.h"

class LightingStrikeBullet: public Bullet
{
public:
	LightingStrikeBullet();
	~LightingStrikeBullet();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);
	
private:

};