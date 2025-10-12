#pragma once

#include "bullet.h"
#include "normal_attack_bullet.h"
#include "fireball_bullet.h"
#include "lighting_strike_bullet.h"
#include "lava_vortex_bullet.h"
#include "lighting_bullet.h"
#include "enemybullet.h"
#include "manager.h"
#include "vector2.h"
#include "ui_manager.h"

#include <vector>

class BulletManager : public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	typedef std::vector<Bullet*> BulletList;

public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	BulletList& get_bullet_list()
	{
		return bullet_list;
	}

	void fire_bullet(BulletName name, std::shared_ptr<Object> target, double speed, Vector2 start_pos, double damage, BuffManager::BuffList list);

	void fire_bullet(BulletName name, Vector2 velocity, double speed, Vector2 start_pos, Vector2 pos, double distance, double damage, BuffManager::BuffList list);

	void fire_bullet(BulletName name, std::shared_ptr<Object> target, double damage, BuffManager::BuffList list);

	void fire_bullet(BulletName name, double damage, double distance, Vector2 pos, BuffManager::BuffList list, double duration = 0.0);

protected:
	BulletManager();
	~BulletManager();

private:
	BulletList bullet_list;

	void remove_invalid_bullet();
};