#pragma once
#include "bullet.h"

class LightingBullet: public Bullet
{
public:
	LightingBullet();
	~LightingBullet();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);
private:
	bool flag = true;

	CollisionManager::CollideBoxList target_list;
	CollisionManager::CollideBoxList box_list;
	std::vector<std::shared_ptr<Vector2>> position_list;

	bool check_repetieion(std::shared_ptr<CollideBox> target);

	void find_way();

	void draw_lighting(SDL_Renderer* renderer, Vector2 pos1, Vector2 pos2);

	void creat_collide_box(std::shared_ptr<CollideBox> target_box);
};