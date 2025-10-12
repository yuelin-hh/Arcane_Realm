#pragma once
#include "bullet.h"

class NormalAttackBullet:public Bullet
{
public:
	NormalAttackBullet();
	~NormalAttackBullet();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	void find_ways_trace(double delta);

	void find_ways_line(double delta);
};