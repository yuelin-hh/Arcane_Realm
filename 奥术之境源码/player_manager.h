#pragma once

#include "manager.h"
#include "config_manager.h"
#include "resources_manager.h"
#include "vector2.h"
#include "player.h"
#include "player_Claude.h"
#include "camera_manager.h"
#include "status_bar_manager.h"

#include <SDL.h>

class PlayerManager : public Manager<PlayerManager>
{
	friend class Manager<PlayerManager>;

protected:
	PlayerManager();
	~PlayerManager();

public:
	void on_enter(int role);

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	bool check_dead()
	{
		return player->is_dead;
	}
private:
	std::unique_ptr<Player> player;
};