#pragma once

#include "manager.h"
#include "config_manager.h"
#include "resources_manager.h"
#include "scene_manager.h"
#include "menu_scene.h"
#include "select_scene.h"
#include "game_scene.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class GameManager :public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv);

protected:
	GameManager();
	~GameManager();

private:

	SDL_Event event;
	bool is_quit = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;	

	std::shared_ptr<Scene> menu_scene;
	std::shared_ptr<Scene> select_scene;
	std::shared_ptr<Scene> game_scene;

	void init_assert(bool flag, const char* err_msg);

	void on_input();

	void on_update(double delta);

	void on_render();
};