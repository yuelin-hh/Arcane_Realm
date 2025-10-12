#pragma once
#include "enemy.h"

class BigSlimeEnemy :public Enemy
{
public:
	BigSlimeEnemy();
	~BigSlimeEnemy();

private:
	std::shared_ptr<CollideBox> attack_box;

	void attack(double delta);

	void is_dead();

	void finish_attack();
};