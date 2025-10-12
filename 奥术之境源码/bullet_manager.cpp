#include "bullet_manager.h"

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{
	for (Bullet* bullet : bullet_list)
		delete bullet;
	bullet_list.clear();
}

void BulletManager::on_update(double delta)
{
	for (Bullet* bullet : bullet_list)
	{
		bullet->on_update(delta);
	}
	remove_invalid_bullet();
}

void BulletManager::on_render(SDL_Renderer* renderer)
{
	for (Bullet* bullet : bullet_list)
		bullet->on_render(renderer);
}

void BulletManager::fire_bullet(BulletName name, std::shared_ptr<Object> target, double speed, Vector2 start_pos, double damage, BuffManager::BuffList list)
{
	UIManager::instance()->ui.on_attack_lock();
	Bullet* bullet = nullptr;
	switch (name)
	{
	case NormalAttack:
		bullet = new NormalAttackBullet();
		break;
	case Lighting:
		bullet = new LightingBullet();
		break;
	default:
		break;
	}
	bullet->set_bullet_parameter(damage, speed, target, start_pos, list);
	bullet_list.push_back(bullet);
}

void BulletManager::fire_bullet(BulletName name, Vector2 velocity, double speed, Vector2 start_pos, Vector2 pos, double distance, double damage, BuffManager::BuffList list)
{
	Bullet* bullet = nullptr;
	switch (name)
	{
	case NormalAttack:
		bullet = new NormalAttackBullet();
		break;
	case Fireball:
		bullet = new FireballBullet();
		break;
	case Enemybullet:
		bullet = new EnemyBullet();
		break;
	default:
		return;
	}
	bullet->set_bullet_parameter(damage, distance, speed, velocity, start_pos, pos, list);
	bullet_list.push_back(bullet);
}

void BulletManager::fire_bullet(BulletName name, std::shared_ptr<Object> target, double damage, BuffManager::BuffList list)
{
	Bullet* bullet = nullptr;
	switch (name)
	{
	case Fireball:
		bullet = new FireballBullet();
		break;
	default:
		return;
	}
	bullet->set_bullet_parameter(damage, target, list);
	bullet_list.push_back(bullet);
}

void BulletManager::fire_bullet(BulletName name, double damage, double distance, Vector2 pos, BuffManager::BuffList list, double duration)
{
	Bullet* bullet = nullptr;
	switch (name)
	{
	case LightingStrike:
		bullet = new LightingStrikeBullet();
		bullet->set_bullet_parameter(damage, distance, pos, list);
		break;
	case LavaVortex:
		bullet = new LavaVortexBullet();
		bullet->set_bullet_parameter(damage, distance, pos, list, duration);
		break;
	default:
		break;
	}


	bullet_list.push_back(bullet);
}

void BulletManager::remove_invalid_bullet()
{
	bullet_list.erase(std::remove_if(bullet_list.begin(), bullet_list.end(),
		[](const Bullet* bullet)
		{
			bool deletable = bullet->can_remove();
			if (deletable) delete bullet;
			return deletable;
		}), bullet_list.end());
}