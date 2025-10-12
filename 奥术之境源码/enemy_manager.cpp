#include "enemy_manager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	enemy_list.clear();
}

void EnemyManager::on_update(double delta)
{
	static bool is_initialized = false;
	if (!is_initialized)
	{
		player_position = CameraManager::instance()->get_player_position();
		is_initialized = true;
	}

	for (std::shared_ptr<Enemy>&enemy : enemy_list)
	{
		enemy->set_player_position(*player_position);
		enemy->on_update(delta);
	}

	remove_invalid_enemy();

	if (enemy_list.size() <= wave)
	{
		spawn_enemy();
	}

	turn_to_object();

	MouseManager::instance()->set_enemylist(object_list);
}

void EnemyManager::on_render(SDL_Renderer* renderer)
{
	for (std::shared_ptr<Enemy>&enemy : enemy_list)
		enemy->on_render(renderer);
}

void EnemyManager::set_gamemod(int gamemode)
{
	this->gamemode = gamemode;
}

void EnemyManager::remove_invalid_enemy()
{
	enemy_list.erase(std::remove_if(enemy_list.begin(), enemy_list.end(),
		[](const std::shared_ptr<Enemy> enemy)
		{
			bool deletable = enemy->can_remove();
			return deletable;
		}), enemy_list.end());
}

void EnemyManager::spawn_enemy()
{
	static bool is_spawned = false;

	std::shared_ptr<Enemy> enemy = nullptr;
	Vector2 pos;
	switch (gamemode)
	{
	case 0:
		for (int i = 0; i < get_random_number(5 * wave, 10 * wave); i++)
		{
			pos.x = get_random_number(50, 1950);
			pos.y = get_random_number(50, 1150);
			if (wave <= 5)
				switch (get_random_number(1, 3))
				{
				case 1:
					enemy = std::make_shared <SlimeEnemy>();
					break;
				case 2:
					enemy = std::make_shared <GunnerEnemy>();
					break;
				default:
					break;
				}
			else
				switch (get_random_number(1, 4))
				{
				case 1:
					enemy = std::make_shared <SlimeEnemy>();
					break;
				case 2:
					enemy = std::make_shared <GunnerEnemy>();
					break;
				case 3:
					enemy = std::make_shared <BigSlimeEnemy>();
					break;
				default:
					break;
				}
			enemy_list.push_back(enemy);
			enemy->set_position(pos);
		}
		wave++;
		break;
	case 1:
		if (is_spawned) break;
		pos.x = 1000;
		pos.y = 600;
		enemy = std::make_shared <DeadmanEnemy>();
		enemy_list.push_back(enemy);
		enemy->set_position(pos);

		pos.x = 1200;
		pos.y = 600;
		//enemy = std::make_shared <DeadmanEnemy>();
		enemy = std::make_shared <GunnerEnemy>();
		enemy_list.push_back(enemy);
		enemy->set_position(pos);

		pos.x = 1400;
		pos.y = 600;
		enemy = std::make_shared <BigSlimeEnemy>();
		enemy_list.push_back(enemy);
		enemy->set_position(pos);

		is_spawned = true;
		break;
	default:
		break;
	}

}

void EnemyManager::turn_to_object()
{
	std::shared_ptr<Object> object;
	object_list.clear();
	for (std::shared_ptr<Enemy> enemy : enemy_list)
	{
		object = enemy;
		object_list.push_back(object);
	}
	MouseManager::instance()->set_enemylist(object_list);
}