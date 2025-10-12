#pragma once

#include "manager.h"
#include "enemy.h"
#include "slime_enemy.h"
#include "big_slime_enemy.h"
#include "deadman_enemy.h"
#include "gunner_enemy.h"
#include "random_number.h"
#include "mouse_manager.h"

#include <vector>
#include <SDL.h>

class EnemyManager : public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;

public:
	typedef std::vector<std::shared_ptr<Enemy>> EnemyList;

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_gamemod(int gamemode);

private:
	int gamemode = 0;
	int wave = 1;
	std::shared_ptr<Vector2> player_position;

	EnemyList enemy_list;
	ObjectList object_list;

	void remove_invalid_enemy();

	void spawn_enemy();

	void turn_to_object();

protected:
	EnemyManager();
	~EnemyManager();
};