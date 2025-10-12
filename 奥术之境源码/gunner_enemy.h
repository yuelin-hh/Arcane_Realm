#pragma once

#include "enemy.h"

class GunnerEnemy:public Enemy
{
public:
	GunnerEnemy();
	~GunnerEnemy();

private:
	void attack(double delta);
};