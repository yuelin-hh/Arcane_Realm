#pragma once
#include "bullet.h"

class EnemyBullet :public Bullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

protected:
	void find_ways(double delta);
};