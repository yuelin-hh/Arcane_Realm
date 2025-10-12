#pragma once
#include "bullet.h"
#include "retention_manager.h"

class LavaVortexBullet :public Bullet
{
public:
	LavaVortexBullet();
	~LavaVortexBullet();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	Timer attack_timer;

	double time = 0;
	double angle = 0;

	bool is_smoking = true;
	bool is_caused_damage = false;
	bool is_finished = false;

	Animation anim_smoke;

	std::shared_ptr<CollideBox> lava_box;
private:
	void check_collide(double delta);
};