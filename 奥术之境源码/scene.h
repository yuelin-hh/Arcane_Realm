#pragma once
#include "config_manager.h"
#include "resources_manager.h"
#include "animation.h"
#include "player_manager.h"
#include "camera_manager.h"
#include "enemy_manager.h"
#include "UI_manager.h"
#include "magic_manager.h"
#include "status_bar_manager.h"
#include "retention_manager.h"
#include "collision_manager.h"
#include "mouse_manager.h"

#include <SDL.h>

class Scene
{
public:
	Scene();
	~Scene();
	virtual void on_enter()
	{

	}

	virtual void on_input(const SDL_Event& event)
	{

	}

	virtual void on_update(double delta)
	{

	}

	virtual void on_render(SDL_Renderer* renderer)
	{

	}

private:

};