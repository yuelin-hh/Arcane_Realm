#pragma once

#include "enemy.h"

class SlimeEnemy :public Enemy
{
public:
	SlimeEnemy();
	~SlimeEnemy();

	

private:
	std::shared_ptr<CollideBox> attack_box;

	void attack(double delta);

	void is_dead();

	void finish_attack();
};